# Waku Waku Hash Function

### Team Name: SushiHacks
### Team Member 1: Anushka Tiwari
### Team Member 2: Vishal Juneja 

We took inspiration from Wang hash and Jenkins Hash to create our own hash function. 

Here is the code for it: 

```cpp
unsigned int hash_function(string text)
{
    const unsigned int prime_modulo = 101;
    unsigned int hash = 121;

    for (char c : text) {
        hash = (hash * 3) + c;

        hash = (hash + 0x7ed55d16) + (hash << 12);
        hash = (hash ^ 0xc761c23c) ^ (hash >> 19);
        hash = (hash + 0x165667b1) + (hash << 5);
        hash = (hash + 0xd3a2646c) ^ (hash << 9);
        hash = (hash + 0xfd7046c5) + (hash << 3);
        hash = (hash ^ 0xb55a4f09) ^ (hash >> 16);

        hash = (hash + 0x7ed55d16) + (hash << 12);
        hash = (hash ^ 0xc761c23c) ^ (hash >> 19);
        hash = (hash + 0x165667b1) + (hash << 5);
        hash = (hash + 0xd3a2646c) ^ (hash << 9);
        hash = (hash + 0xfd7046c5) + (hash << 3);
        hash = (hash ^ 0xb55a4f09) ^ (hash >> 16);
    }

    return hash % prime_modulo; // Take modulo to fit in array size
}
```

We achieved randomness by doing a set of bitwise operations, which are done in similar pattern in wang hash and jenkins hash. Later on we did did mod with prime number. We chose 101 because most of the test cases had slots near to 100 and 101 is the closest prime number to it.

Later on we wanted to get the best possible standard deviation, for that we bruteforced our constant `hash` and `m` (replaced with 3) using the following code: 

```bash
#!/bin/bash

for seed in $(seq 26 256); do
    for m in $(seq 0 256); do
        i=0
        sum=0
        for file in ./inputs/*; do
            echo -n "$file : "
            output=$(./encoder $seed $m <"$file" | tail -n 1)
            echo $output $seed $m
            sum=$(python3 -c "print($output + $sum)")
            i=$((i + 1))
        done

        echo "average std dev = $(python3 -c "print($sum / $i)") $seed $m"

        echo "============================================"

        i=0
        sum=0

        for file in ./inputs/*; do
            echo -n "$file : "
            output=$(./demo_encoder <"$file" | tail -n 1)
            echo $output
            sum=$(python3 -c "print($output + $sum)")
            i=$((i + 1))
        done

        echo "average std dev = $(python3 -c "print($sum / $i)")"
    done
done
```

we observed that we got the best possible average standard deviation of 1.5469 :

```
./inputs/atoz.txt : 0.748331
./inputs/bertuncased.txt : 2.0529
./inputs/common500.txt : 2.2
./inputs/mit_a.txt : 1.98494
./inputs/sample_input.txt : 0.748331
average std dev = 1.5469004000000002
```


References:
1. Wang Hash: https://naml.us/post/inverse-of-a-hash-function/
2. Hash Function FAQ: https://burtleburtle.net/bob/hash/hashfaq.html
3. Hash Functions and block ciphers: https://burtleburtle.net/bob/hash/
4. Hash functions for hash table lookup: https://burtleburtle.net/bob/hash/evahash.html#universal
5. spooky hash: https://burtleburtle.net/bob/hash/spooky.html
6. Jenkins Hash function: https://en.wikipedia.org/wiki/Jenkins_hash_function
