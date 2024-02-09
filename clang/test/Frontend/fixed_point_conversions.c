// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN: %clang_cc1 -ffixed-point -triple x86_64-unknown-linux-gnu -S -emit-llvm %s -o - | FileCheck %s --check-prefixes=CHECK,SIGNED
// RUN: %clang_cc1 -ffixed-point -triple x86_64-unknown-linux-gnu -S -emit-llvm %s -o - -fpadding-on-unsigned-fixed-point | FileCheck %s --check-prefixes=CHECK,UNSIGNED

short _Accum sa;
_Accum a, a2;
long _Accum la;

unsigned short _Accum usa;
unsigned _Accum ua;
unsigned long _Accum ula;

short _Fract sf;
_Fract f;
long _Fract lf;
unsigned _Fract uf;

_Sat short _Accum sat_sa;
_Sat _Accum sat_a;
_Sat long _Accum sat_la;

_Sat unsigned short _Accum sat_usa;
_Sat unsigned _Accum sat_ua;
_Sat unsigned long _Accum sat_ula;

_Sat short _Fract sat_sf;
_Sat _Fract sat_f;
_Sat long _Fract sat_lf;
_Sat unsigned _Fract sat_uf;

short s;
int i;
unsigned int ui;

float fl;
double d;

// CHECK-LABEL: @fix_same1(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @a, align 4
// CHECK-NEXT:    store i32 [[TMP0]], i32* @a2, align 4
// CHECK-NEXT:    ret void
//
void fix_same1(void) {
  a2 = a;
}

// CHECK-LABEL: @fix_same2(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @a, align 4
// CHECK-NEXT:    store i32 [[TMP0]], i32* @a2, align 4
// CHECK-NEXT:    ret void
//
void fix_same2(void) {
  a2 = (_Accum)a;
}


// CHECK-LABEL: @fix_castdown1(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i64, i64* @la, align 8
// CHECK-NEXT:    [[DOWNSCALE:%.*]] = ashr i64 [[TMP0]], 16
// CHECK-NEXT:    [[RESIZE:%.*]] = trunc i64 [[DOWNSCALE]] to i32
// CHECK-NEXT:    store i32 [[RESIZE]], i32* @a, align 4
// CHECK-NEXT:    ret void
//
void fix_castdown1(void) {
  a = la;
}

// CHECK-LABEL: @fix_castdown2(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i64, i64* @la, align 8
// CHECK-NEXT:    [[DOWNSCALE:%.*]] = ashr i64 [[TMP0]], 16
// CHECK-NEXT:    [[RESIZE:%.*]] = trunc i64 [[DOWNSCALE]] to i32
// CHECK-NEXT:    store i32 [[RESIZE]], i32* @a, align 4
// CHECK-NEXT:    ret void
//
void fix_castdown2(void) {
  a = (_Accum)la;
}

// CHECK-LABEL: @fix_castdown3(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @a, align 4
// CHECK-NEXT:    [[DOWNSCALE:%.*]] = ashr i32 [[TMP0]], 8
// CHECK-NEXT:    [[RESIZE:%.*]] = trunc i32 [[DOWNSCALE]] to i16
// CHECK-NEXT:    store i16 [[RESIZE]], i16* @sa, align 2
// CHECK-NEXT:    ret void
//
void fix_castdown3(void) {
  sa = a;
}

// CHECK-LABEL: @fix_castdown4(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @a, align 4
// CHECK-NEXT:    [[DOWNSCALE:%.*]] = ashr i32 [[TMP0]], 8
// CHECK-NEXT:    [[RESIZE:%.*]] = trunc i32 [[DOWNSCALE]] to i16
// CHECK-NEXT:    store i16 [[RESIZE]], i16* @sa, align 2
// CHECK-NEXT:    ret void
//
void fix_castdown4(void) {
  sa = a;
}


// CHECK-LABEL: @fix_castup1(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i16, i16* @sa, align 2
// CHECK-NEXT:    [[RESIZE:%.*]] = sext i16 [[TMP0]] to i32
// CHECK-NEXT:    [[UPSCALE:%.*]] = shl i32 [[RESIZE]], 8
// CHECK-NEXT:    store i32 [[UPSCALE]], i32* @a, align 4
// CHECK-NEXT:    ret void
//
void fix_castup1(void) {
  a = sa;
}

// CHECK-LABEL: @fix_castup2(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i16, i16* @sa, align 2
// CHECK-NEXT:    [[RESIZE:%.*]] = sext i16 [[TMP0]] to i32
// CHECK-NEXT:    [[UPSCALE:%.*]] = shl i32 [[RESIZE]], 8
// CHECK-NEXT:    store i32 [[UPSCALE]], i32* @a, align 4
// CHECK-NEXT:    ret void
//
void fix_castup2(void) {
  a = (_Accum)sa;
}

// CHECK-LABEL: @fix_castup3(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i64, i64* @la, align 8
// CHECK-NEXT:    [[DOWNSCALE:%.*]] = ashr i64 [[TMP0]], 16
// CHECK-NEXT:    [[RESIZE:%.*]] = trunc i64 [[DOWNSCALE]] to i32
// CHECK-NEXT:    store i32 [[RESIZE]], i32* @a, align 4
// CHECK-NEXT:    ret void
//
void fix_castup3(void) {
  a = la;
}

// CHECK-LABEL: @fix_castup4(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i64, i64* @la, align 8
// CHECK-NEXT:    [[DOWNSCALE:%.*]] = ashr i64 [[TMP0]], 16
// CHECK-NEXT:    [[RESIZE:%.*]] = trunc i64 [[DOWNSCALE]] to i32
// CHECK-NEXT:    store i32 [[RESIZE]], i32* @a, align 4
// CHECK-NEXT:    ret void
//
void fix_castup4(void) {
  a = (long _Accum)la;
}


// SIGNED-LABEL: @fix_sign1(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @a, align 4
// SIGNED-NEXT:    [[UPSCALE:%.*]] = shl i32 [[TMP0]], 1
// SIGNED-NEXT:    store i32 [[UPSCALE]], i32* @ua, align 4
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @fix_sign1(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @a, align 4
// UNSIGNED-NEXT:    store i32 [[TMP0]], i32* @ua, align 4
// UNSIGNED-NEXT:    ret void
//
void fix_sign1(void) {
  ua = a;
}

// SIGNED-LABEL: @fix_sign2(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @ua, align 4
// SIGNED-NEXT:    [[DOWNSCALE:%.*]] = lshr i32 [[TMP0]], 1
// SIGNED-NEXT:    store i32 [[DOWNSCALE]], i32* @a, align 4
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @fix_sign2(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @ua, align 4
// UNSIGNED-NEXT:    store i32 [[TMP0]], i32* @a, align 4
// UNSIGNED-NEXT:    ret void
//
void fix_sign2(void) {
  a = ua;
}

// SIGNED-LABEL: @fix_sign3(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @a, align 4
// SIGNED-NEXT:    [[UPSCALE:%.*]] = shl i32 [[TMP0]], 1
// SIGNED-NEXT:    store i32 [[UPSCALE]], i32* @ua, align 4
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @fix_sign3(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @a, align 4
// UNSIGNED-NEXT:    store i32 [[TMP0]], i32* @ua, align 4
// UNSIGNED-NEXT:    ret void
//
void fix_sign3(void) {
  ua = (unsigned _Accum)a;
}

// SIGNED-LABEL: @fix_sign4(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @ua, align 4
// SIGNED-NEXT:    [[DOWNSCALE:%.*]] = lshr i32 [[TMP0]], 1
// SIGNED-NEXT:    store i32 [[DOWNSCALE]], i32* @a, align 4
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @fix_sign4(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @ua, align 4
// UNSIGNED-NEXT:    store i32 [[TMP0]], i32* @a, align 4
// UNSIGNED-NEXT:    ret void
//
void fix_sign4(void) {
  a = (_Accum)ua;
}

// SIGNED-LABEL: @fix_sign5(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @a, align 4
// SIGNED-NEXT:    [[RESIZE:%.*]] = sext i32 [[TMP0]] to i64
// SIGNED-NEXT:    [[UPSCALE:%.*]] = shl i64 [[RESIZE]], 17
// SIGNED-NEXT:    store i64 [[UPSCALE]], i64* @ula, align 8
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @fix_sign5(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @a, align 4
// UNSIGNED-NEXT:    [[RESIZE:%.*]] = sext i32 [[TMP0]] to i64
// UNSIGNED-NEXT:    [[UPSCALE:%.*]] = shl i64 [[RESIZE]], 16
// UNSIGNED-NEXT:    store i64 [[UPSCALE]], i64* @ula, align 8
// UNSIGNED-NEXT:    ret void
//
void fix_sign5(void) {
  ula = a;
}


// CHECK-LABEL: @fix_sat1(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @sat_a, align 4
// CHECK-NEXT:    [[DOWNSCALE:%.*]] = ashr i32 [[TMP0]], 8
// CHECK-NEXT:    [[TMP1:%.*]] = icmp sgt i32 [[DOWNSCALE]], 32767
// CHECK-NEXT:    [[SATMAX:%.*]] = select i1 [[TMP1]], i32 32767, i32 [[DOWNSCALE]]
// CHECK-NEXT:    [[TMP2:%.*]] = icmp slt i32 [[SATMAX]], -32768
// CHECK-NEXT:    [[SATMIN:%.*]] = select i1 [[TMP2]], i32 -32768, i32 [[SATMAX]]
// CHECK-NEXT:    [[RESIZE:%.*]] = trunc i32 [[SATMIN]] to i16
// CHECK-NEXT:    store i16 [[RESIZE]], i16* @sat_sa, align 2
// CHECK-NEXT:    ret void
//
void fix_sat1(void) {
  // Casting down between types
  sat_sa = sat_a;
}

// CHECK-LABEL: @fix_sat2(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @sat_a, align 4
// CHECK-NEXT:    [[DOWNSCALE:%.*]] = ashr i32 [[TMP0]], 8
// CHECK-NEXT:    [[TMP1:%.*]] = icmp sgt i32 [[DOWNSCALE]], 127
// CHECK-NEXT:    [[SATMAX:%.*]] = select i1 [[TMP1]], i32 127, i32 [[DOWNSCALE]]
// CHECK-NEXT:    [[TMP2:%.*]] = icmp slt i32 [[SATMAX]], -128
// CHECK-NEXT:    [[SATMIN:%.*]] = select i1 [[TMP2]], i32 -128, i32 [[SATMAX]]
// CHECK-NEXT:    [[RESIZE:%.*]] = trunc i32 [[SATMIN]] to i8
// CHECK-NEXT:    store i8 [[RESIZE]], i8* @sat_sf, align 1
// CHECK-NEXT:    ret void
//
void fix_sat2(void) {
  // Accum to Fract, decreasing scale
  sat_sf = sat_a;
}

// CHECK-LABEL: @fix_sat3(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @a, align 4
// CHECK-NEXT:    [[TMP1:%.*]] = icmp sgt i32 [[TMP0]], 32767
// CHECK-NEXT:    [[SATMAX:%.*]] = select i1 [[TMP1]], i32 32767, i32 [[TMP0]]
// CHECK-NEXT:    [[TMP2:%.*]] = icmp slt i32 [[SATMAX]], -32768
// CHECK-NEXT:    [[SATMIN:%.*]] = select i1 [[TMP2]], i32 -32768, i32 [[SATMAX]]
// CHECK-NEXT:    [[RESIZE:%.*]] = trunc i32 [[SATMIN]] to i16
// CHECK-NEXT:    store i16 [[RESIZE]], i16* @sat_f, align 2
// CHECK-NEXT:    ret void
//
void fix_sat3(void) {
  // Accum to Fract, same scale
  sat_f = a;
}

// CHECK-LABEL: @fix_sat4(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @sat_a, align 4
// CHECK-NEXT:    [[RESIZE:%.*]] = sext i32 [[TMP0]] to i48
// CHECK-NEXT:    [[UPSCALE:%.*]] = shl i48 [[RESIZE]], 16
// CHECK-NEXT:    [[TMP1:%.*]] = icmp sgt i48 [[UPSCALE]], 2147483647
// CHECK-NEXT:    [[SATMAX:%.*]] = select i1 [[TMP1]], i48 2147483647, i48 [[UPSCALE]]
// CHECK-NEXT:    [[TMP2:%.*]] = icmp slt i48 [[SATMAX]], -2147483648
// CHECK-NEXT:    [[SATMIN:%.*]] = select i1 [[TMP2]], i48 -2147483648, i48 [[SATMAX]]
// CHECK-NEXT:    [[RESIZE1:%.*]] = trunc i48 [[SATMIN]] to i32
// CHECK-NEXT:    store i32 [[RESIZE1]], i32* @sat_lf, align 4
// CHECK-NEXT:    ret void
//
void fix_sat4(void) {
  // Accum to Fract, increasing scale
  sat_lf = sat_a;
}

// SIGNED-LABEL: @fix_sat5(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @sat_a, align 4
// SIGNED-NEXT:    [[DOWNSCALE:%.*]] = ashr i32 [[TMP0]], 7
// SIGNED-NEXT:    [[TMP1:%.*]] = icmp sgt i32 [[DOWNSCALE]], 65535
// SIGNED-NEXT:    [[SATMAX:%.*]] = select i1 [[TMP1]], i32 65535, i32 [[DOWNSCALE]]
// SIGNED-NEXT:    [[TMP2:%.*]] = icmp slt i32 [[SATMAX]], 0
// SIGNED-NEXT:    [[SATMIN:%.*]] = select i1 [[TMP2]], i32 0, i32 [[SATMAX]]
// SIGNED-NEXT:    [[RESIZE:%.*]] = trunc i32 [[SATMIN]] to i16
// SIGNED-NEXT:    store i16 [[RESIZE]], i16* @sat_usa, align 2
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @fix_sat5(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @sat_a, align 4
// UNSIGNED-NEXT:    [[DOWNSCALE:%.*]] = ashr i32 [[TMP0]], 8
// UNSIGNED-NEXT:    [[TMP1:%.*]] = icmp sgt i32 [[DOWNSCALE]], 32767
// UNSIGNED-NEXT:    [[SATMAX:%.*]] = select i1 [[TMP1]], i32 32767, i32 [[DOWNSCALE]]
// UNSIGNED-NEXT:    [[TMP2:%.*]] = icmp slt i32 [[SATMAX]], 0
// UNSIGNED-NEXT:    [[SATMIN:%.*]] = select i1 [[TMP2]], i32 0, i32 [[SATMAX]]
// UNSIGNED-NEXT:    [[RESIZE:%.*]] = trunc i32 [[SATMIN]] to i16
// UNSIGNED-NEXT:    store i16 [[RESIZE]], i16* @sat_usa, align 2
// UNSIGNED-NEXT:    ret void
//
void fix_sat5(void) {
  // Signed to unsigned, decreasing scale
  sat_usa = sat_a;
}

// SIGNED-LABEL: @fix_sat6(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @sat_a, align 4
// SIGNED-NEXT:    [[RESIZE:%.*]] = sext i32 [[TMP0]] to i33
// SIGNED-NEXT:    [[UPSCALE:%.*]] = shl i33 [[RESIZE]], 1
// SIGNED-NEXT:    [[TMP1:%.*]] = icmp slt i33 [[UPSCALE]], 0
// SIGNED-NEXT:    [[SATMIN:%.*]] = select i1 [[TMP1]], i33 0, i33 [[UPSCALE]]
// SIGNED-NEXT:    [[RESIZE1:%.*]] = trunc i33 [[SATMIN]] to i32
// SIGNED-NEXT:    store i32 [[RESIZE1]], i32* @sat_ua, align 4
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @fix_sat6(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @sat_a, align 4
// UNSIGNED-NEXT:    [[TMP1:%.*]] = icmp slt i32 [[TMP0]], 0
// UNSIGNED-NEXT:    [[SATMIN:%.*]] = select i1 [[TMP1]], i32 0, i32 [[TMP0]]
// UNSIGNED-NEXT:    store i32 [[SATMIN]], i32* @sat_ua, align 4
// UNSIGNED-NEXT:    ret void
//
void fix_sat6(void) {
  // Signed to unsigned, increasing scale
  sat_ua = sat_a;
}

// CHECK-LABEL: @fix_sat7(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @a, align 4
// CHECK-NEXT:    store i32 [[TMP0]], i32* @sat_a, align 4
// CHECK-NEXT:    ret void
//
void fix_sat7(void) {
  // Nothing when saturating to the same type and size
  sat_a = a;
}

// CHECK-LABEL: @fix_sat8(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @sat_a, align 4
// CHECK-NEXT:    store i32 [[TMP0]], i32* @a, align 4
// CHECK-NEXT:    ret void
//
void fix_sat8(void) {
  // Nothing when assigning back
  a = sat_a;
}

// CHECK-LABEL: @fix_sat9(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i16, i16* @sat_f, align 2
// CHECK-NEXT:    [[RESIZE:%.*]] = sext i16 [[TMP0]] to i32
// CHECK-NEXT:    store i32 [[RESIZE]], i32* @sat_a, align 4
// CHECK-NEXT:    ret void
//
void fix_sat9(void) {
  // No overflow when casting from fract to signed accum
  sat_a = sat_f;
}

// SIGNED-LABEL: @fix_sat10(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load i8, i8* @sat_sf, align 1
// SIGNED-NEXT:    [[RESIZE:%.*]] = sext i8 [[TMP0]] to i32
// SIGNED-NEXT:    [[UPSCALE:%.*]] = shl i32 [[RESIZE]], 9
// SIGNED-NEXT:    [[TMP1:%.*]] = icmp slt i32 [[UPSCALE]], 0
// SIGNED-NEXT:    [[SATMIN:%.*]] = select i1 [[TMP1]], i32 0, i32 [[UPSCALE]]
// SIGNED-NEXT:    store i32 [[SATMIN]], i32* @sat_ua, align 4
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @fix_sat10(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load i8, i8* @sat_sf, align 1
// UNSIGNED-NEXT:    [[RESIZE:%.*]] = sext i8 [[TMP0]] to i32
// UNSIGNED-NEXT:    [[UPSCALE:%.*]] = shl i32 [[RESIZE]], 8
// UNSIGNED-NEXT:    [[TMP1:%.*]] = icmp slt i32 [[UPSCALE]], 0
// UNSIGNED-NEXT:    [[SATMIN:%.*]] = select i1 [[TMP1]], i32 0, i32 [[UPSCALE]]
// UNSIGNED-NEXT:    store i32 [[SATMIN]], i32* @sat_ua, align 4
// UNSIGNED-NEXT:    ret void
//
void fix_sat10(void) {
  // Only get overflow checking if signed fract to unsigned accum
  sat_ua = sat_sf;
}


// CHECK-LABEL: @fix_fract1(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @a, align 4
// CHECK-NEXT:    [[DOWNSCALE:%.*]] = ashr i32 [[TMP0]], 8
// CHECK-NEXT:    [[RESIZE:%.*]] = trunc i32 [[DOWNSCALE]] to i8
// CHECK-NEXT:    store i8 [[RESIZE]], i8* @sf, align 1
// CHECK-NEXT:    ret void
//
void fix_fract1(void) {
  // To lower scale
  sf = a;
}

// CHECK-LABEL: @fix_fract2(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i8, i8* @sf, align 1
// CHECK-NEXT:    [[RESIZE:%.*]] = sext i8 [[TMP0]] to i32
// CHECK-NEXT:    [[UPSCALE:%.*]] = shl i32 [[RESIZE]], 8
// CHECK-NEXT:    store i32 [[UPSCALE]], i32* @a, align 4
// CHECK-NEXT:    ret void
//
void fix_fract2(void) {
  // To higher scale
  a = sf;
}

// CHECK-LABEL: @fix_fract3(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @a, align 4
// CHECK-NEXT:    [[RESIZE:%.*]] = trunc i32 [[TMP0]] to i16
// CHECK-NEXT:    store i16 [[RESIZE]], i16* @f, align 2
// CHECK-NEXT:    ret void
//
void fix_fract3(void) {
  // To same scale
  f = a;
}

// CHECK-LABEL: @fix_fract4(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i16, i16* @f, align 2
// CHECK-NEXT:    [[RESIZE:%.*]] = sext i16 [[TMP0]] to i32
// CHECK-NEXT:    store i32 [[RESIZE]], i32* @a, align 4
// CHECK-NEXT:    ret void
//
void fix_fract4(void) {
  a = f;
}

// CHECK-LABEL: @fix_fract5(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i16, i16* @uf, align 2
// CHECK-NEXT:    [[RESIZE:%.*]] = zext i16 [[TMP0]] to i32
// CHECK-NEXT:    store i32 [[RESIZE]], i32* @ua, align 4
// CHECK-NEXT:    ret void
//
void fix_fract5(void) {
  // To unsigned
  ua = uf;
}

// CHECK-LABEL: @fix_fract6(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @ua, align 4
// CHECK-NEXT:    [[RESIZE:%.*]] = trunc i32 [[TMP0]] to i16
// CHECK-NEXT:    store i16 [[RESIZE]], i16* @uf, align 2
// CHECK-NEXT:    ret void
//
void fix_fract6(void) {
  uf = ua;
}


// CHECK-LABEL: @fix_int1(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i16, i16* @sa, align 2
// CHECK-NEXT:    [[TMP1:%.*]] = icmp slt i16 [[TMP0]], 0
// CHECK-NEXT:    [[TMP2:%.*]] = add i16 [[TMP0]], 127
// CHECK-NEXT:    [[TMP3:%.*]] = select i1 [[TMP1]], i16 [[TMP2]], i16 [[TMP0]]
// CHECK-NEXT:    [[DOWNSCALE:%.*]] = ashr i16 [[TMP3]], 7
// CHECK-NEXT:    [[RESIZE:%.*]] = sext i16 [[DOWNSCALE]] to i32
// CHECK-NEXT:    store i32 [[RESIZE]], i32* @i, align 4
// CHECK-NEXT:    ret void
//
void fix_int1(void) {
  // Will need to check for negative values
  i = sa;
}

// SIGNED-LABEL: @fix_int2(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load i16, i16* @usa, align 2
// SIGNED-NEXT:    [[DOWNSCALE:%.*]] = lshr i16 [[TMP0]], 8
// SIGNED-NEXT:    [[RESIZE:%.*]] = zext i16 [[DOWNSCALE]] to i32
// SIGNED-NEXT:    store i32 [[RESIZE]], i32* @i, align 4
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @fix_int2(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load i16, i16* @usa, align 2
// UNSIGNED-NEXT:    [[DOWNSCALE:%.*]] = lshr i16 [[TMP0]], 7
// UNSIGNED-NEXT:    [[RESIZE:%.*]] = zext i16 [[DOWNSCALE]] to i32
// UNSIGNED-NEXT:    store i32 [[RESIZE]], i32* @i, align 4
// UNSIGNED-NEXT:    ret void
//
void fix_int2(void) {
  // No check needed for unsigned fixed points. Can just right shift.
  i = usa;
}


// CHECK-LABEL: @int_fix1(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @i, align 4
// CHECK-NEXT:    [[RESIZE:%.*]] = trunc i32 [[TMP0]] to i16
// CHECK-NEXT:    [[UPSCALE:%.*]] = shl i16 [[RESIZE]], 7
// CHECK-NEXT:    store i16 [[UPSCALE]], i16* @sa, align 2
// CHECK-NEXT:    ret void
//
void int_fix1(void) {
  sa = i;
}

// CHECK-LABEL: @int_fix2(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @ui, align 4
// CHECK-NEXT:    [[RESIZE:%.*]] = trunc i32 [[TMP0]] to i16
// CHECK-NEXT:    [[UPSCALE:%.*]] = shl i16 [[RESIZE]], 7
// CHECK-NEXT:    store i16 [[UPSCALE]], i16* @sa, align 2
// CHECK-NEXT:    ret void
//
void int_fix2(void) {
  sa = ui;
}

// SIGNED-LABEL: @int_fix3(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @i, align 4
// SIGNED-NEXT:    [[RESIZE:%.*]] = trunc i32 [[TMP0]] to i16
// SIGNED-NEXT:    [[UPSCALE:%.*]] = shl i16 [[RESIZE]], 8
// SIGNED-NEXT:    store i16 [[UPSCALE]], i16* @usa, align 2
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @int_fix3(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @i, align 4
// UNSIGNED-NEXT:    [[RESIZE:%.*]] = trunc i32 [[TMP0]] to i16
// UNSIGNED-NEXT:    [[UPSCALE:%.*]] = shl i16 [[RESIZE]], 7
// UNSIGNED-NEXT:    store i16 [[UPSCALE]], i16* @usa, align 2
// UNSIGNED-NEXT:    ret void
//
void int_fix3(void) {
  usa = i;
}

// SIGNED-LABEL: @int_fix4(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @ui, align 4
// SIGNED-NEXT:    [[RESIZE:%.*]] = trunc i32 [[TMP0]] to i16
// SIGNED-NEXT:    [[UPSCALE:%.*]] = shl i16 [[RESIZE]], 8
// SIGNED-NEXT:    store i16 [[UPSCALE]], i16* @usa, align 2
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @int_fix4(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @ui, align 4
// UNSIGNED-NEXT:    [[RESIZE:%.*]] = trunc i32 [[TMP0]] to i16
// UNSIGNED-NEXT:    [[UPSCALE:%.*]] = shl i16 [[RESIZE]], 7
// UNSIGNED-NEXT:    store i16 [[UPSCALE]], i16* @usa, align 2
// UNSIGNED-NEXT:    ret void
//
void int_fix4(void) {
  usa = ui;
}

// CHECK-LABEL: @int_fix5(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i16, i16* @s, align 2
// CHECK-NEXT:    [[RESIZE:%.*]] = sext i16 [[TMP0]] to i64
// CHECK-NEXT:    [[UPSCALE:%.*]] = shl i64 [[RESIZE]], 31
// CHECK-NEXT:    store i64 [[UPSCALE]], i64* @la, align 8
// CHECK-NEXT:    ret void
//
void int_fix5(void) {
  la = s;
}


// CHECK-LABEL: @int_sat1(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @i, align 4
// CHECK-NEXT:    [[RESIZE:%.*]] = sext i32 [[TMP0]] to i39
// CHECK-NEXT:    [[UPSCALE:%.*]] = shl i39 [[RESIZE]], 7
// CHECK-NEXT:    [[TMP1:%.*]] = icmp sgt i39 [[UPSCALE]], 32767
// CHECK-NEXT:    [[SATMAX:%.*]] = select i1 [[TMP1]], i39 32767, i39 [[UPSCALE]]
// CHECK-NEXT:    [[TMP2:%.*]] = icmp slt i39 [[SATMAX]], -32768
// CHECK-NEXT:    [[SATMIN:%.*]] = select i1 [[TMP2]], i39 -32768, i39 [[SATMAX]]
// CHECK-NEXT:    [[RESIZE1:%.*]] = trunc i39 [[SATMIN]] to i16
// CHECK-NEXT:    store i16 [[RESIZE1]], i16* @sat_sa, align 2
// CHECK-NEXT:    ret void
//
void int_sat1(void) {
  sat_sa = i;
}

// CHECK-LABEL: @int_sat2(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @ui, align 4
// CHECK-NEXT:    [[RESIZE:%.*]] = zext i32 [[TMP0]] to i39
// CHECK-NEXT:    [[UPSCALE:%.*]] = shl i39 [[RESIZE]], 7
// CHECK-NEXT:    [[TMP1:%.*]] = icmp ugt i39 [[UPSCALE]], 32767
// CHECK-NEXT:    [[SATMAX:%.*]] = select i1 [[TMP1]], i39 32767, i39 [[UPSCALE]]
// CHECK-NEXT:    [[RESIZE1:%.*]] = trunc i39 [[SATMAX]] to i16
// CHECK-NEXT:    store i16 [[RESIZE1]], i16* @sat_sa, align 2
// CHECK-NEXT:    ret void
//
void int_sat2(void) {
  sat_sa = ui;
}

// SIGNED-LABEL: @int_sat3(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @i, align 4
// SIGNED-NEXT:    [[RESIZE:%.*]] = sext i32 [[TMP0]] to i40
// SIGNED-NEXT:    [[UPSCALE:%.*]] = shl i40 [[RESIZE]], 8
// SIGNED-NEXT:    [[TMP1:%.*]] = icmp sgt i40 [[UPSCALE]], 65535
// SIGNED-NEXT:    [[SATMAX:%.*]] = select i1 [[TMP1]], i40 65535, i40 [[UPSCALE]]
// SIGNED-NEXT:    [[TMP2:%.*]] = icmp slt i40 [[SATMAX]], 0
// SIGNED-NEXT:    [[SATMIN:%.*]] = select i1 [[TMP2]], i40 0, i40 [[SATMAX]]
// SIGNED-NEXT:    [[RESIZE1:%.*]] = trunc i40 [[SATMIN]] to i16
// SIGNED-NEXT:    store i16 [[RESIZE1]], i16* @sat_usa, align 2
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @int_sat3(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @i, align 4
// UNSIGNED-NEXT:    [[RESIZE:%.*]] = sext i32 [[TMP0]] to i39
// UNSIGNED-NEXT:    [[UPSCALE:%.*]] = shl i39 [[RESIZE]], 7
// UNSIGNED-NEXT:    [[TMP1:%.*]] = icmp sgt i39 [[UPSCALE]], 32767
// UNSIGNED-NEXT:    [[SATMAX:%.*]] = select i1 [[TMP1]], i39 32767, i39 [[UPSCALE]]
// UNSIGNED-NEXT:    [[TMP2:%.*]] = icmp slt i39 [[SATMAX]], 0
// UNSIGNED-NEXT:    [[SATMIN:%.*]] = select i1 [[TMP2]], i39 0, i39 [[SATMAX]]
// UNSIGNED-NEXT:    [[RESIZE1:%.*]] = trunc i39 [[SATMIN]] to i16
// UNSIGNED-NEXT:    store i16 [[RESIZE1]], i16* @sat_usa, align 2
// UNSIGNED-NEXT:    ret void
//
void int_sat3(void) {
  sat_usa = i;
}

// SIGNED-LABEL: @int_sat4(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @ui, align 4
// SIGNED-NEXT:    [[RESIZE:%.*]] = zext i32 [[TMP0]] to i40
// SIGNED-NEXT:    [[UPSCALE:%.*]] = shl i40 [[RESIZE]], 8
// SIGNED-NEXT:    [[TMP1:%.*]] = icmp ugt i40 [[UPSCALE]], 65535
// SIGNED-NEXT:    [[SATMAX:%.*]] = select i1 [[TMP1]], i40 65535, i40 [[UPSCALE]]
// SIGNED-NEXT:    [[RESIZE1:%.*]] = trunc i40 [[SATMAX]] to i16
// SIGNED-NEXT:    store i16 [[RESIZE1]], i16* @sat_usa, align 2
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @int_sat4(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @ui, align 4
// UNSIGNED-NEXT:    [[RESIZE:%.*]] = zext i32 [[TMP0]] to i39
// UNSIGNED-NEXT:    [[UPSCALE:%.*]] = shl i39 [[RESIZE]], 7
// UNSIGNED-NEXT:    [[TMP1:%.*]] = icmp ugt i39 [[UPSCALE]], 32767
// UNSIGNED-NEXT:    [[SATMAX:%.*]] = select i1 [[TMP1]], i39 32767, i39 [[UPSCALE]]
// UNSIGNED-NEXT:    [[RESIZE1:%.*]] = trunc i39 [[SATMAX]] to i16
// UNSIGNED-NEXT:    store i16 [[RESIZE1]], i16* @sat_usa, align 2
// UNSIGNED-NEXT:    ret void
//
void int_sat4(void) {
  sat_usa = ui;
}


// CHECK-LABEL: @float_fix1(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load float, float* @fl, align 4
// CHECK-NEXT:    [[TMP1:%.*]] = fmul float [[TMP0]], 1.280000e+02
// CHECK-NEXT:    [[TMP2:%.*]] = fptosi float [[TMP1]] to i16
// CHECK-NEXT:    store i16 [[TMP2]], i16* @sa, align 2
// CHECK-NEXT:    ret void
//
void float_fix1(void) {
  sa = fl;
}

// CHECK-LABEL: @float_fix2(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load float, float* @fl, align 4
// CHECK-NEXT:    [[TMP1:%.*]] = fmul float [[TMP0]], 3.276800e+04
// CHECK-NEXT:    [[TMP2:%.*]] = fptosi float [[TMP1]] to i32
// CHECK-NEXT:    store i32 [[TMP2]], i32* @a, align 4
// CHECK-NEXT:    ret void
//
void float_fix2(void) {
  a = fl;
}

// CHECK-LABEL: @float_fix3(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load float, float* @fl, align 4
// CHECK-NEXT:    [[TMP1:%.*]] = fmul float [[TMP0]], 0x41E0000000000000
// CHECK-NEXT:    [[TMP2:%.*]] = fptosi float [[TMP1]] to i64
// CHECK-NEXT:    store i64 [[TMP2]], i64* @la, align 8
// CHECK-NEXT:    ret void
//
void float_fix3(void) {
  la = fl;
}

// CHECK-LABEL: @float_fix4(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load float, float* @fl, align 4
// CHECK-NEXT:    [[TMP1:%.*]] = fmul float [[TMP0]], 1.280000e+02
// CHECK-NEXT:    [[TMP2:%.*]] = fptosi float [[TMP1]] to i8
// CHECK-NEXT:    store i8 [[TMP2]], i8* @sf, align 1
// CHECK-NEXT:    ret void
//
void float_fix4(void) {
  sf = fl;
}

// CHECK-LABEL: @float_fix5(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load float, float* @fl, align 4
// CHECK-NEXT:    [[TMP1:%.*]] = fmul float [[TMP0]], 0x41E0000000000000
// CHECK-NEXT:    [[TMP2:%.*]] = fptosi float [[TMP1]] to i32
// CHECK-NEXT:    store i32 [[TMP2]], i32* @lf, align 4
// CHECK-NEXT:    ret void
//
void float_fix5(void) {
  lf = fl;
}

// SIGNED-LABEL: @float_fix6(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load float, float* @fl, align 4
// SIGNED-NEXT:    [[TMP1:%.*]] = fmul float [[TMP0]], 6.553600e+04
// SIGNED-NEXT:    [[TMP2:%.*]] = fptoui float [[TMP1]] to i32
// SIGNED-NEXT:    store i32 [[TMP2]], i32* @ua, align 4
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @float_fix6(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load float, float* @fl, align 4
// UNSIGNED-NEXT:    [[TMP1:%.*]] = fmul float [[TMP0]], 3.276800e+04
// UNSIGNED-NEXT:    [[TMP2:%.*]] = fptosi float [[TMP1]] to i32
// UNSIGNED-NEXT:    store i32 [[TMP2]], i32* @ua, align 4
// UNSIGNED-NEXT:    ret void
//
void float_fix6(void) {
  ua = fl;
}

// SIGNED-LABEL: @float_fix7(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load float, float* @fl, align 4
// SIGNED-NEXT:    [[TMP1:%.*]] = fmul float [[TMP0]], 6.553600e+04
// SIGNED-NEXT:    [[TMP2:%.*]] = fptoui float [[TMP1]] to i16
// SIGNED-NEXT:    store i16 [[TMP2]], i16* @uf, align 2
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @float_fix7(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load float, float* @fl, align 4
// UNSIGNED-NEXT:    [[TMP1:%.*]] = fmul float [[TMP0]], 3.276800e+04
// UNSIGNED-NEXT:    [[TMP2:%.*]] = fptosi float [[TMP1]] to i16
// UNSIGNED-NEXT:    store i16 [[TMP2]], i16* @uf, align 2
// UNSIGNED-NEXT:    ret void
//
void float_fix7(void) {
  uf = fl;
}


// CHECK-LABEL: @fix_float1(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i16, i16* @sa, align 2
// CHECK-NEXT:    [[TMP1:%.*]] = sitofp i16 [[TMP0]] to float
// CHECK-NEXT:    [[TMP2:%.*]] = fmul float [[TMP1]], 7.812500e-03
// CHECK-NEXT:    store float [[TMP2]], float* @fl, align 4
// CHECK-NEXT:    ret void
//
void fix_float1(void) {
  fl = sa;
}

// CHECK-LABEL: @fix_float2(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @a, align 4
// CHECK-NEXT:    [[TMP1:%.*]] = sitofp i32 [[TMP0]] to float
// CHECK-NEXT:    [[TMP2:%.*]] = fmul float [[TMP1]], 0x3F00000000000000
// CHECK-NEXT:    store float [[TMP2]], float* @fl, align 4
// CHECK-NEXT:    ret void
//
void fix_float2(void) {
  fl = a;
}

// CHECK-LABEL: @fix_float3(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i64, i64* @la, align 8
// CHECK-NEXT:    [[TMP1:%.*]] = sitofp i64 [[TMP0]] to float
// CHECK-NEXT:    [[TMP2:%.*]] = fmul float [[TMP1]], 0x3E00000000000000
// CHECK-NEXT:    store float [[TMP2]], float* @fl, align 4
// CHECK-NEXT:    ret void
//
void fix_float3(void) {
  fl = la;
}

// CHECK-LABEL: @fix_float4(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i8, i8* @sf, align 1
// CHECK-NEXT:    [[TMP1:%.*]] = sitofp i8 [[TMP0]] to float
// CHECK-NEXT:    [[TMP2:%.*]] = fmul float [[TMP1]], 7.812500e-03
// CHECK-NEXT:    store float [[TMP2]], float* @fl, align 4
// CHECK-NEXT:    ret void
//
void fix_float4(void) {
  fl = sf;
}

// CHECK-LABEL: @fix_float5(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* @lf, align 4
// CHECK-NEXT:    [[TMP1:%.*]] = sitofp i32 [[TMP0]] to float
// CHECK-NEXT:    [[TMP2:%.*]] = fmul float [[TMP1]], 0x3E00000000000000
// CHECK-NEXT:    store float [[TMP2]], float* @fl, align 4
// CHECK-NEXT:    ret void
//
void fix_float5(void) {
  fl = lf;
}

// SIGNED-LABEL: @fix_float6(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @ua, align 4
// SIGNED-NEXT:    [[TMP1:%.*]] = uitofp i32 [[TMP0]] to float
// SIGNED-NEXT:    [[TMP2:%.*]] = fmul float [[TMP1]], 0x3EF0000000000000
// SIGNED-NEXT:    store float [[TMP2]], float* @fl, align 4
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @fix_float6(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load i32, i32* @ua, align 4
// UNSIGNED-NEXT:    [[TMP1:%.*]] = uitofp i32 [[TMP0]] to float
// UNSIGNED-NEXT:    [[TMP2:%.*]] = fmul float [[TMP1]], 0x3F00000000000000
// UNSIGNED-NEXT:    store float [[TMP2]], float* @fl, align 4
// UNSIGNED-NEXT:    ret void
//
void fix_float6(void) {
  fl = ua;
}

// SIGNED-LABEL: @fix_float7(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load i16, i16* @uf, align 2
// SIGNED-NEXT:    [[TMP1:%.*]] = uitofp i16 [[TMP0]] to float
// SIGNED-NEXT:    [[TMP2:%.*]] = fmul float [[TMP1]], 0x3EF0000000000000
// SIGNED-NEXT:    store float [[TMP2]], float* @fl, align 4
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @fix_float7(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load i16, i16* @uf, align 2
// UNSIGNED-NEXT:    [[TMP1:%.*]] = uitofp i16 [[TMP0]] to float
// UNSIGNED-NEXT:    [[TMP2:%.*]] = fmul float [[TMP1]], 0x3F00000000000000
// UNSIGNED-NEXT:    store float [[TMP2]], float* @fl, align 4
// UNSIGNED-NEXT:    ret void
//
void fix_float7(void) {
  fl = uf;
}


// CHECK-LABEL: @float_sat1(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load float, float* @fl, align 4
// CHECK-NEXT:    [[TMP1:%.*]] = fmul float [[TMP0]], 1.280000e+02
// CHECK-NEXT:    [[TMP2:%.*]] = call i16 @llvm.fptosi.sat.i16.f32(float [[TMP1]])
// CHECK-NEXT:    store i16 [[TMP2]], i16* @sat_sa, align 2
// CHECK-NEXT:    ret void
//
void float_sat1(void) {
  sat_sa = fl;
}

// CHECK-LABEL: @float_sat2(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load float, float* @fl, align 4
// CHECK-NEXT:    [[TMP1:%.*]] = fmul float [[TMP0]], 3.276800e+04
// CHECK-NEXT:    [[TMP2:%.*]] = call i32 @llvm.fptosi.sat.i32.f32(float [[TMP1]])
// CHECK-NEXT:    store i32 [[TMP2]], i32* @sat_a, align 4
// CHECK-NEXT:    ret void
//
void float_sat2(void) {
  sat_a = fl;
}

// CHECK-LABEL: @float_sat3(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load float, float* @fl, align 4
// CHECK-NEXT:    [[TMP1:%.*]] = fmul float [[TMP0]], 0x41E0000000000000
// CHECK-NEXT:    [[TMP2:%.*]] = call i64 @llvm.fptosi.sat.i64.f32(float [[TMP1]])
// CHECK-NEXT:    store i64 [[TMP2]], i64* @sat_la, align 8
// CHECK-NEXT:    ret void
//
void float_sat3(void) {
  sat_la = fl;
}

// CHECK-LABEL: @float_sat4(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load float, float* @fl, align 4
// CHECK-NEXT:    [[TMP1:%.*]] = fmul float [[TMP0]], 1.280000e+02
// CHECK-NEXT:    [[TMP2:%.*]] = call i8 @llvm.fptosi.sat.i8.f32(float [[TMP1]])
// CHECK-NEXT:    store i8 [[TMP2]], i8* @sat_sf, align 1
// CHECK-NEXT:    ret void
//
void float_sat4(void) {
  sat_sf = fl;
}

// SIGNED-LABEL: @float_sat5(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load float, float* @fl, align 4
// SIGNED-NEXT:    [[TMP1:%.*]] = fmul float [[TMP0]], 6.553600e+04
// SIGNED-NEXT:    [[TMP2:%.*]] = call i32 @llvm.fptoui.sat.i32.f32(float [[TMP1]])
// SIGNED-NEXT:    store i32 [[TMP2]], i32* @sat_ua, align 4
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @float_sat5(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load float, float* @fl, align 4
// UNSIGNED-NEXT:    [[TMP1:%.*]] = fmul float [[TMP0]], 3.276800e+04
// UNSIGNED-NEXT:    [[TMP2:%.*]] = call i32 @llvm.fptosi.sat.i32.f32(float [[TMP1]])
// UNSIGNED-NEXT:    [[TMP3:%.*]] = icmp slt i32 [[TMP2]], 0
// UNSIGNED-NEXT:    [[SATMIN:%.*]] = select i1 [[TMP3]], i32 0, i32 [[TMP2]]
// UNSIGNED-NEXT:    store i32 [[SATMIN]], i32* @sat_ua, align 4
// UNSIGNED-NEXT:    ret void
//
void float_sat5(void) {
  sat_ua = fl;
}

// SIGNED-LABEL: @float_sat6(
// SIGNED-NEXT:  entry:
// SIGNED-NEXT:    [[TMP0:%.*]] = load float, float* @fl, align 4
// SIGNED-NEXT:    [[TMP1:%.*]] = fmul float [[TMP0]], 6.553600e+04
// SIGNED-NEXT:    [[TMP2:%.*]] = call i16 @llvm.fptoui.sat.i16.f32(float [[TMP1]])
// SIGNED-NEXT:    store i16 [[TMP2]], i16* @sat_uf, align 2
// SIGNED-NEXT:    ret void
//
// UNSIGNED-LABEL: @float_sat6(
// UNSIGNED-NEXT:  entry:
// UNSIGNED-NEXT:    [[TMP0:%.*]] = load float, float* @fl, align 4
// UNSIGNED-NEXT:    [[TMP1:%.*]] = fmul float [[TMP0]], 3.276800e+04
// UNSIGNED-NEXT:    [[TMP2:%.*]] = call i16 @llvm.fptosi.sat.i16.f32(float [[TMP1]])
// UNSIGNED-NEXT:    [[TMP3:%.*]] = icmp slt i16 [[TMP2]], 0
// UNSIGNED-NEXT:    [[SATMIN:%.*]] = select i1 [[TMP3]], i16 0, i16 [[TMP2]]
// UNSIGNED-NEXT:    store i16 [[SATMIN]], i16* @sat_uf, align 2
// UNSIGNED-NEXT:    ret void
//
void float_sat6(void) {
  sat_uf = fl;
}
