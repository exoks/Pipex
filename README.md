# **Pipex42** #
Pipex is a project from 42 coding school that recreates a simple version of shell pipes (`|`) in C. It allows you to connect multiple commands, so the output of one command becomes the input of the next, just like in a real shell, It also supports HEREDOC mode which lets you provide input directly in the terminal.

#### **What Pipex Does** : ####
* Reads input from a **file** or **command**.
* Passes the output of one command to the next using **pipes**.
* Writes the final output to another file.
* Uses system calls like `pipe()`, `fork()`, `execve()`, and `waitpid()` to manage processes and communication.

### **Example Usage** : ###
1|-> Run the following sh cmd:
```sh 
make
```
2|-> usage example
```sh 
./pipex infile "cmd1" "cmd2" outfile
```
**NOTE**:
It works exactly like this in the shell:
```sh 
< infile cmd1 | cmd2 > outfile
```
**This means**:

1_ cmd1 reads from infile

2_ cmd1 sends its output to cmd2 through a pipe

3_ cmd2 writes its final output to outfile

---
