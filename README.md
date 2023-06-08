# CS50 Speller

This repository contains an implementation of a spell-checker program, based on the problem set specifications from Harvard's [CS50](https://cs50.harvard.edu) course. The challenge in this assignment is to implement the fastest spell-checker possible using a hash table data structure. 

The spell-checker operates by loading a dictionary of words into memory, then checks an input text file for misspelled words. 

## Hash Function

The hash function in this solution serves to convert a word into a numerical index that can be used in our hash table.

Here is the `hash` function:

```c
// Hashes word to a number
unsigned int hash(const char *word)
{
    int x = 0;
    for (int i = 0; i < LENGTH + 1; i++)
    {
        if (word[i] == '\0')
        {
            return (x % N);
        }
        else
        {
            x = 23 * tolower(word[i]) + x;
        }
    }
    printf("Error\n");
    return false;
}
```

This hash function begins by initializing a variable `x` to 0. It then loops through each character of the input word up to `LENGTH + 1` times. If a null character (`\0`) is encountered, which indicates the end of the string, it returns the current value of `x` modulo `N` (where `N` is the number of buckets in the hash table).

If the character is not null, the function performs a computation on the lower case version of the character: it multiplies the ASCII value of the character by 23 and then adds it to the current value of `x`. This is a simple polynomial hash function where 23 is chosen as a multiplier. 

In case the function fails to return within the loop (which should not happen with correct program logic), an error message is printed to the standard output and the function returns `false`. 

This hash function ensures that the hash values are evenly distributed for different words and reduces the chances of collisions, thereby making our hash table efficient. Moreover, this hash function is case-insensitive as it converts all characters to lower case before computing the hash value.


## Getting Started

1. Download or clone this repository.
2. Open a terminal and navigate to the root directory of the project.
3. Run `make` to compile the program.

## Usage

The usage of the speller is as follows:
```
./speller [dictionary] text
```
Here, `dictionary` is a file containing a list of lowercase words, one per line, and `text` is a file to be spell-checked. The `dictionary` argument is optional; if omitted, `speller` will use the `dictionaries/large` by default. 

For example, to spell-check a file named `myfile.txt` using the default dictionary, you would run:
```
./speller myfile.txt
```

And to use a specific dictionary, `mydictionary.txt`, you would run:
```
./speller mydictionary.txt myfile.txt
```

## Implementation

This solution involves implementing five functions in `dictionary.c`: 

1. `load` - Loads dictionary into memory.
2. `hash` - Returns a hash value for a given word.
3. `size` - Returns the number of words in the dictionary.
4. `check` - Checks if a word is in the dictionary.
5. `unload` - Unloads the dictionary from memory, freeing up the used space.

Note: The `dictionary.h` file contains the declarations of these functions, which are to be used in the `dictionary.c` implementation file.

## Testing

Various text files for testing can be found in the `texts/` directory. These include scripts, excerpts from legal documents, and works of literature. To use one for spell-checking, simply pass it as the `text` argument when running `speller`.

## Disclaimer

Please note that the problem set specifications are owned by [Harvard University](https://www.harvard.edu/) and this solution is only meant as a guide, not for plagiarism.
