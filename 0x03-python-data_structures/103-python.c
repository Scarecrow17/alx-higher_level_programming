#include <stdio.h>
#include <Python.h>

/**
 * print_python_bytes - Prints information
 * @p: Python Object
 * Return: no return
 */
void print_python_bytes(PyObject *p)
{
	char *strng;
	long int size, p, limit;

	printf("[.] bytes object info\n");
	if (!PyBytes_Check(p))
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}

	size = ((PyVarObject *)(p))->ob_size;
	strng = ((PyBytesObject *)p)->ob_sval;

	printf("  size: %ld\n", size);
	printf("  trying strng: %s\n", strng);

	if (size >= 10)
		limit = 10;
	else
		limit = size + 1;

	printf("  first %ld bytes:", limit);

	for (p = 0; p < limit; p++)
		if (strng[p] >= 0)
			printf(" %02x", strng[p]);
		else
			printf(" %02x", 256 + strng[p]);

	printf("\n");
}

/**
 * print_python_list - Prints information
 * @p: Python Object
 * Return: no return
 */
void print_python_list(PyObject *p)
{
	long int size, p;
	PyListObject *list;
	PyObject *obj;

	size = ((PyVarObject *)(p))->ob_size;
	list = (PyListObject *)p;

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %ld\n", size);
	printf("[*] Allocated = %ld\n", list->allocated);

	for (p = 0; p < size; p++)
	{
		obj = ((PyListObject *)p)->ob_item[p];
		printf("Element %ld: %s\n", p, ((obj)->ob_type)->tp_name);
		if (PyBytes_Check(obj))
			print_python_bytes(obj);
	}
}
