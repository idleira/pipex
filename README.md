# pipex - @42Wolfsburg
## description
pipex takes the project aimed to better understand shell redirection and pipes, by handling them in C.

the program takes an input file, performs a command on it, pipes the result to another command which then writes its result to an output file.

program's arguments are processed the same as < infile cmd1 | cmd2 > outfile in shell.

the result copiesthe output of this shell command: `$ < input_file command1 | command2 > output file`

## 

here are some **resources** i used:

• [creating and killing child processes in c](https://www.codequoi.com/en/creating-and-killing-child-processes-in-c/)

• [pipe: an inter-process communication method](https://www.codequoi.com/en/pipe-an-inter-process-communication-method/)

• [handling a file by its descriptor in c](https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/)

• [a comprehensive guide to pipex](https://reactive.so/post/42-a-comprehensive-guide-to-pipex)

## 

```
# ./pipex infile cmd1 cmd2 outfile
pipe()
 |
 |-- fork()
      |
      |-- child // cmd1
      :     |--dup2()
      :     |--close end[0]
      :     |--execve(cmd1)
      :
      |-- parent // cmd2
            |--dup2()
            |--close end[1]
            |--execve(cmd2)
 
# pipe() sends the output of the first execve() as input to the second execve()
# fork() runs two processes (i.e. two commands) in one single program
# dup2() swaps our files with stdin and stdout

```
## usage
1. clone this repository: `git clone git@github.com:idleira/pipex.git pipex && cd pipex`

2. use `make` to compile the project

3. run the program with shell commands in this order: `./pipex <infile> <cmd1> <cmd2> <outfile>`

## my final grade
![pipex grade](https://github.com/idleira/pipex/assets/127216218/ee27e75a-7737-449c-a430-e206a50ceb22)
