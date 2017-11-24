#include <iostream>

void trace(const char *pMsg){ cout << "List : " << pMsg << endl; }

#define SUCCESS 0
#define FAILURE 1

typedef int data_t 
typedef int result_t 

class List 
{
public:
  		 List();
  		~List(); 
		result_t __stdcall insert_end	(data_t n_data);
		result_t __stdcall find_data	(data_t e_data);

private:
		struct node
		{
			node_t *next;
			data_t *data;
		};
		typedef struct node node_t;
		typedef struct node list_t;
		list_t *HEAD;

		node_t 	 __stdcall search_node (data_t e_data);	
		node_t 	 __stdcall get_last_node ();	
};

List::List()
{
	list_t *ptr = (list_t *)calloc(1, sizeof(list_t));
	if (ptr == NULL)
	{
		trace("calloc : OUT_OF_MEMORY");
		exit(1);
	}
	HEAD = ptr;
	HEAD -> next = NULL;
	HEAD -> data = NULL;
}

List::~List()
{
	node_t *tmp, *run = HEAD -> next;
	while(run != NULL)
	{
		tmp = run -> next;
		free(run);
		run = tmp;
	}
	free(HEAD);
}

result_t List::insert_end(data_t n_data)
{
	list_t *ptr =  (list_t *)calloc(1, sizeof(list_t));
	if (ptr == NULL)
	{
		trace("calloc : OUT_OF_MEMORY");
		exit(1);
	}
	list_t *last_node 	= getlastnode();
	last_node -> next 	= ptr; 
	ptr -> next 		= NULL;
	ptr -> data 		= n_data;

	return SUCCESS;
}

result_t List::find_data(data_t e_data)
{
	if (search_node(e_data) == NULL)
		return FAILURE;
	else 
		return SUCCESS;
}

node_t List::search_node(data_t e_data)
{
	node_t *run = HEAD;

	while(run != NULL)
	{
		if (run -> data = e_data)
			return run;
		run = run -> next;
	}
	return NULL; 
}

node_t List::get_last_node()
{
	node_t *run = HEAD;

	while(run -> next != NULL)
	{
		run = run -> next;
	}
	return run; 
}