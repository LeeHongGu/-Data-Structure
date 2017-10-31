#include "BookList.h"
#include "CommonHeader.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	if (!argv[1])
		argv[1] = "";

	BookList bl(argv[1]);

	bl.showMenu();
}