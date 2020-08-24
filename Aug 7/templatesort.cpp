#include <iostream>
#include <string.h>

using namespace std;

template <class T>
void bubbleSort(T arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

template <class T>
void sort(T arr[], int size, char const *argv)
{
    bubbleSort(arr, size);

    if (strcmp(argv, "1") == 0)
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";

    if (strcmp(argv, "0") == 0)
        for (int i = size - 1; i >= 0; i--)
            cout << arr[i] << " ";

    cout << endl;
}

void error(int x)
{
	if(x==0)
    cout << "syntax: ./tsort <0-des/1-asc> [<integers>/<decimals>/<strings>]" << endl;
    else
    cout<<"Array isn't of same datatype! Aborting."<<endl;
}

int main(int argc, char const *argv[])
{
    int size = argc - 2; //2 is offset
    int count = 0;

    if (argc <= 2)
    {
        error(0);
        return EXIT_FAILURE;
    }

i:	if(count<size)
	{
		for(int i=0; i<size; i++)
		{
			if (strspn(argv[i+2], "-0123456789") == strlen(argv[i+2]))
				count++;
		}
		
		if(count!=size && count>0)
		{	
			error(1);
			return EXIT_FAILURE;
		}
		
		else if(count == size)
		{
			int arr[size];
			for (int i = 0; i < size; i++)
            arr[i] = stoi(argv[i+2]);

        	sort<int>(arr, size, argv[1]);
        	return EXIT_SUCCESS;
		}
		
		else 
			goto f;
	}
	
 
 f: 	for(int i=0; i<size; i++)
		{
			if( strspn(argv[i+2],".") == 1 || strspn(argv[i+2],"-0.") == 2 || ( strspn(argv[i+2],"-0.")==3 && strspn(argv[i+2],"-") == 1 ) )
			{	
				if (strspn(argv[i+2], "-.0123456789") == strlen(argv[i+2]))
					count++;
			}
		}
		
		if(count!=size && count>0)
		{
			error(1);
			return EXIT_FAILURE;
		}
		
		else if(count == size)
		{
			double arr[size];
			for (int i = 0; i < size; i++)
            arr[i] = stod(argv[i+2]);

        	sort<double>(arr, size, argv[1]);
        	return EXIT_SUCCESS;
		}
		
		else 
			goto s; 
 

 s: 	for(int i=0; i<size; i++)
		{
			if (isalpha(*argv[i+2]))
				count++;
		}
		
		if(count!=size && count>0)
		{
			error(1);
			return EXIT_FAILURE;
		}
		
		else if(count == size)
		{	
			string arr[size];
			for (int i = 0; i < size; i++)
            arr[i] = (string)(argv[i+2]);
            
        	sort<string>(arr, size, argv[1]);
        	return EXIT_SUCCESS;
		} 
}
