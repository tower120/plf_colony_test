### benchmarking `plf::colony` vs `std::vector` in terms of iteration speed, after elements erase.

`plf::colony` slow downs linearly to wasted space:
```
int capacity = 1'000'000;
float erase_probability = 90;
```

Output:
```
colony
 [99735] 806 (49954948722)
vector
 [100000] 90 (4999950000)
 ```