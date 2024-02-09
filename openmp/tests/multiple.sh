
echo "taskloop mix"
for i in {1..5}; do
    ./taskloop_mix
done

echo "taskloop_jacobi"
for i in {1..5}; do
    ./taskloop_jacobi
done

echo "taskloop_matmul"
for i in {1..5}; do
    ./taskloop_matmul
done


echo "taskloop_memcpy"
for i in {1..5}; do
    ./taskloop_memcpy
done


echo "taskloop_memory"
for i in {1..5}; do
    ./taskloop_memory
done



echo "taskloop_memory2"
for i in {1..5}; do
    ./taskloop_memory2
done



