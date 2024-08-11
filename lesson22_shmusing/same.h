#pragma once
#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <cstring>
#include <unistd.h>
#define PATHNAME "."
#define PROJ_ID 123
#define SIZE 4096
mode_t mode = 0660;

