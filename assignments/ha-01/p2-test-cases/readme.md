## Generating and encoding random IP addresses
To generate a number of random IP addresses/masks and save their encodings into a binary file, the provided python script can be used.  It takes two command line arguments:
- `output_file_name`: the name of the binary file to be created
- `N`: the number of IP addresses

The example below generates a file with 5 IP addresses.
```bash
$ python3 generator.py file-5.bin 5
```

To generate multiple files using the same script, an alternative can be a `bash` loop.  The list of different lenghts can be easily modified.
 
```bash
$ for i in 1 5 10 25 50 100 1000; do python3 generator.py file-$i.bin $i; done
```

