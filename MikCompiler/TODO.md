# TODO

- Preprocessor
- Filter compiler generated @file and @fend out in error messaging

- Idea: on_change(i) {<execute on alteration>}

- Implement typecast function definition like:
    ```
        // declares typecast: int->int
        fn typecast(int a)->int {
            return a
        }
    ```
# Parser
- Arrays
- Bounds
- custom guards

- array acces and array definition

## Arrays
everything concerning arrays will be implemented after the basics are done

## Bounds ans guards
Smae goes for custom guards and bounds

## Functions

Implement Functions like:
```
    // declare a normal function
    fn a(int a, str b) -> int

    // define a function
    fn a(int a, str b) -> int {
        return atoi(b)+a
    }
```

Alternatively a function can be a typecast function
```
    // declare typecast from int->int
    fn typecast(int a) -> int {
        return a
    }
```

## Pre-/post_change
A pre_change/post_change makro may be defined as:
```
    // declare a custom pre_change action. In this example, i is normalizes to zero before every change
    pre_change(i) {
        i = 0
    }

    // declare a custom post_change action. In this example i is kept within a bound of (-inf, 10]
    post_change(i) {
        if i > 10 {
            i = 10
        }
    }
```

pre_/post_change will not call a function with specified body, but will rather paste the code either before or after the alteration of the variable. Meaning, that the example above would be turned into

```
// pre_change
i = 0
// pre_change

i = 11 // actual variable alteration. the post and pre are not visible to the user and are directly implemented into the llvm-ir!

// post_change
if i > 10 {
    i = 10
}
// post_change
```

