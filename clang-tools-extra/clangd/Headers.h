//===--- Headers.h - Include headers -----------------------------*- C++-*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANGD_HEADERS_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANGD_HEADERS_H

#include "Protocol.h"
#include "SourceCode.h"
#include "index/Symbol.h"
#include "support/Logger.h"
#include "support/Path.h"
#include "clang/Basic/FileEntry.h"
#include "clang/Basic/TokenKinds.h"
#include "clang/Format/Format.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/HeaderSearch.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Tooling/Inclusions/HeaderIncludes.h"
#include "clang/Tooling/Inclusions/StandardLibrary.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/StringSet.h"
#include "llvm/Support/Error.h"
#include "llvm/Support/FileSystem/UniqueID.h"
#include "llvm/Support/VirtualFileSystem.h"
#include <string>

namespace clang {
namespace clangd {

/// Returns true if \p Include is literal include like "path" or <path>.
bool isLiteralInclude(llvm::StringRef Include);

/// Represents a header file to be #include'd.
struct HeaderFile {
  std::string File;
  /// If this is true, `File` is a literal string quoted with <> or "" that
  /// can be #included directly; otherwise, `File` is an absolute file path.
  bool Verbatim;

  bool valid() const;
};

/// Creates a `HeaderFile` from \p Header which can be either a URI or a literal
/// include.
llvm::Expected<HeaderFile> toHeaderFile(llvm::StringRef Header,
                                        llvm::StringRef HintPath);

// Returns include headers for \p Sym sorted by popularity. If two headers are
// equally popular, prefer the shorter one.
llvm::SmallVector<llvm::StringRef, 1> getRankedIncludes(const Symbol &Sym);

// An #include directive that we found in the main file.
struct Inclusion {
  tok::PPKeywordKind Directive; // Directive used for inclusion, e.g. import
  std::string Written;          // Inclusion name as written e.g. <vector>.
  Path Resolved; // Resolved path of included file. Empty if not resolved.
  unsigned HashOffset = 0; // Byte offset from start of file to #.
  int HashLine = 0;        // Line number containing the directive, 0-indexed.
  SrcMgr::CharacteristicKind FileKind = SrcMgr::C_User;
  llvm::Optional<unsigned> HeaderID;
  bool BehindPragmaKeep = false; // Has IWYU pragma: keep right after.
};
llvm::raw_ostream &operator<<(llvm::raw_ostream &, const Inclusion &);
bool operator==(const Inclusion &LHS, const Inclusion &RHS);

// Contains information about one file in the build graph and its direct
// dependencies. Doesn't own the strings it references (IncludeGraph is
// self-contained).
struct IncludeGraphNode {
  enum class SourceFlag : uint8_t {
    None = 0,
    // Whether current file is a main file rather than a header.
    IsTU = 1 << 0,
    // Whether current file had any uncompilable errors during indexing.
    HadErrors = 1 << 1,
  };

  SourceFlag Flags = SourceFlag::None;
  llvm::StringRef URI;
  FileDigest Digest{{0}};
  std::vector<llvm::StringRef> DirectIncludes;
};
// FileURI and FileInclusions are references to keys of the map containing
// them.
// Important: The graph generated by those callbacks might contain cycles, self
// edges and multi edges.
using IncludeGraph = llvm::StringMap<IncludeGraphNode>;

inline IncludeGraphNode::SourceFlag operator|(IncludeGraphNode::SourceFlag A,
                                              IncludeGraphNode::SourceFlag B) {
  return static_cast<IncludeGraphNode::SourceFlag>(static_cast<uint8_t>(A) |
                                                   static_cast<uint8_t>(B));
}

inline bool operator&(IncludeGraphNode::SourceFlag A,
                      IncludeGraphNode::SourceFlag B) {
  return static_cast<uint8_t>(A) & static_cast<uint8_t>(B);
}

inline IncludeGraphNode::SourceFlag &
operator|=(IncludeGraphNode::SourceFlag &A, IncludeGraphNode::SourceFlag B) {
  return A = A | B;
}

// Information captured about the inclusion graph in a translation unit.
// This includes detailed information about the direct #includes, and summary
// information about all transitive includes.
//
// It should be built incrementally with collectIncludeStructureCallback().
// When we build the preamble, we capture and store its include structure along
// with the preamble data. When we use the preamble, we can copy its
// IncludeStructure and use another collectIncludeStructureCallback() to fill
// in any non-preamble inclusions.
class IncludeStructure {
public:
  IncludeStructure() {
    // Reserve HeaderID = 0 for the main file.
    RealPathNames.emplace_back();
  }

  // Inserts a PPCallback and CommentHandler that visits all includes in the
  // main file and populates the structure. It will also scan for IWYU pragmas
  // in comments.
  void collect(const CompilerInstance &CI);

  // HeaderID identifies file in the include graph. It corresponds to a
  // FileEntry rather than a FileID, but stays stable across preamble & main
  // file builds.
  enum class HeaderID : unsigned {};

  llvm::Optional<HeaderID> getID(const FileEntry *Entry) const;
  HeaderID getOrCreateID(const FileEntry *Entry);

  StringRef getRealPath(HeaderID ID) const {
    assert(static_cast<unsigned>(ID) <= RealPathNames.size());
    return RealPathNames[static_cast<unsigned>(ID)];
  }

  bool isSelfContained(HeaderID ID) const {
    return !NonSelfContained.contains(ID);
  }

  // Return all transitively reachable files.
  llvm::ArrayRef<std::string> allHeaders() const { return RealPathNames; }

  // Return all transitively reachable files, and their minimum include depth.
  // All transitive includes (absolute paths), with their minimum include depth.
  // Root --> 0, #included file --> 1, etc.
  // Root is the ID of the header being visited first.
  llvm::DenseMap<HeaderID, unsigned>
  includeDepth(HeaderID Root = MainFileID) const;

  // Maps HeaderID to the ids of the files included from it.
  llvm::DenseMap<HeaderID, SmallVector<HeaderID>> IncludeChildren;

  llvm::DenseMap<tooling::stdlib::Header, llvm::SmallVector<HeaderID>>
      StdlibHeaders;

  std::vector<Inclusion> MainFileIncludes;

  // We reserve HeaderID(0) for the main file and will manually check for that
  // in getID and getOrCreateID because the UniqueID is not stable when the
  // content of the main file changes.
  static const HeaderID MainFileID = HeaderID(0u);

  class RecordHeaders;

private:
  // MainFileEntry will be used to check if the queried file is the main file
  // or not.
  const FileEntry *MainFileEntry = nullptr;

  std::vector<std::string> RealPathNames; // In HeaderID order.
  // FileEntry::UniqueID is mapped to the internal representation (HeaderID).
  // Identifying files in a way that persists from preamble build to subsequent
  // builds is surprisingly hard. FileID is unavailable in InclusionDirective(),
  // and RealPathName and UniqueID are not preserved in
  // the preamble.
  llvm::DenseMap<llvm::sys::fs::UniqueID, HeaderID> UIDToIndex;
  // Contains HeaderIDs of all non self-contained entries in the
  // IncludeStructure.
  llvm::DenseSet<HeaderID> NonSelfContained;
};

// Calculates insertion edit for including a new header in a file.
class IncludeInserter {
public:
  // If \p HeaderSearchInfo is nullptr (e.g. when compile command is
  // infeasible), this will only try to insert verbatim headers, and
  // include path of non-verbatim header will not be shortened.
  IncludeInserter(StringRef FileName, StringRef Code,
                  const format::FormatStyle &Style, StringRef BuildDir,
                  HeaderSearch *HeaderSearchInfo)
      : FileName(FileName), Code(Code), BuildDir(BuildDir),
        HeaderSearchInfo(HeaderSearchInfo),
        Inserter(FileName, Code, Style.IncludeStyle) {}

  void addExisting(const Inclusion &Inc);

  /// Checks whether to add an #include of the header into \p File.
  /// An #include will not be added if:
  ///   - Either \p DeclaringHeader or \p InsertedHeader is already (directly)
  ///   in \p Inclusions (including those included via different paths).
  ///   - \p DeclaringHeader or \p InsertedHeader is the same as \p File.
  ///
  /// \param DeclaringHeader is path of the original header corresponding to \p
  /// InsertedHeader e.g. the header that declares a symbol.
  /// \param InsertedHeader The preferred header to be inserted. This could be
  /// the same as DeclaringHeader but must be provided.
  bool shouldInsertInclude(PathRef DeclaringHeader,
                           const HeaderFile &InsertedHeader) const;

  /// Determines the preferred way to #include a file, taking into account the
  /// search path. Usually this will prefer a shorter representation like
  /// 'Foo/Bar.h' over a longer one like 'Baz/include/Foo/Bar.h'.
  ///
  /// \param InsertedHeader The preferred header to be inserted.
  ///
  /// \param IncludingFile is the absolute path of the file that InsertedHeader
  /// will be inserted.
  ///
  /// \return A quoted "path" or <path> to be included, or None if it couldn't
  /// be shortened.
  llvm::Optional<std::string>
  calculateIncludePath(const HeaderFile &InsertedHeader,
                       llvm::StringRef IncludingFile) const;

  /// Calculates an edit that inserts \p VerbatimHeader into code. If the header
  /// is already included, this returns None.
  llvm::Optional<TextEdit> insert(llvm::StringRef VerbatimHeader) const;

private:
  StringRef FileName;
  StringRef Code;
  StringRef BuildDir;
  HeaderSearch *HeaderSearchInfo = nullptr;
  llvm::StringSet<> IncludedHeaders; // Both written and resolved.
  tooling::HeaderIncludes Inserter;  // Computers insertion replacement.
};

} // namespace clangd
} // namespace clang

namespace llvm {

// Support HeaderIDs as DenseMap keys.
template <> struct DenseMapInfo<clang::clangd::IncludeStructure::HeaderID> {
  static inline clang::clangd::IncludeStructure::HeaderID getEmptyKey() {
    return static_cast<clang::clangd::IncludeStructure::HeaderID>(-1);
  }

  static inline clang::clangd::IncludeStructure::HeaderID getTombstoneKey() {
    return static_cast<clang::clangd::IncludeStructure::HeaderID>(-2);
  }

  static unsigned
  getHashValue(const clang::clangd::IncludeStructure::HeaderID &Tag) {
    return hash_value(static_cast<unsigned>(Tag));
  }

  static bool isEqual(const clang::clangd::IncludeStructure::HeaderID &LHS,
                      const clang::clangd::IncludeStructure::HeaderID &RHS) {
    return LHS == RHS;
  }
};

} // namespace llvm

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANGD_HEADERS_H
