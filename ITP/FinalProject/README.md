# Final Project

This project was done individually. The original code I had written had had its different functions and variables split accross multiple `.c` files, but I couldn't find them; so here is only the "single-source-file" version.

## Building and running

This project uses [CLUI](https://github.com/SBU-CE/clui) to show a nice TUI (somewhat like `htop`) to the user. It is included here, so just make sure the `lib` directory and its content are present along the `todo.c` file. 

Then use your favourite C compiler:

```bash
cd ITP/FinalProject
gcc -o todo todo.c
```

Then simply run it using `./todo`.
