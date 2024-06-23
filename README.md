# smolDB

Simple, performant key value store

## Description

This database uses a B+ tree to store key, value tuples on the disk. Each node in the B+ tree is a slotted page to allow variable sized keys.

## Getting Started

### Dependencies

* Any Linux distro will probably work

### Build

* Run `make` in the project root

### Executing program

* Run `make` and then `./smoldb`
```
> i key_here value_here     # inserts key, value pair
> dr                        # this displays the root node
```

## Help

If the data file gets corrupted, run the following command:
```
rm btree.dat
```

## Acknowledgments

Inspiration, code snippets, etc.
* [awesome-readme](https://github.com/matiassingers/awesome-readme)