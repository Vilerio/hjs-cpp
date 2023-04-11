# HJS
A header library for storing and accessing hierarchical data for C++11, which uses the JSON structure. (Hierarchical JSON storage for C++).
<br/> <br/>
# HJS documentation
## Installation
Installing hjs is very simple, you just have to put the files available in the "include" folder of the repo in the same directory as your main c++ 11 file (often main.cpp). Once this is done, you have to include the header with these lines : <br/> <br/>
```#include "hjs.hpp"``` <br/>
```#include "json.hpp``` <br/>

Once the header is included, you can use it !

## Usage
### Hjs Intitialization
To initialize HJS correctly, you must use the "hjs_init" function and then the "hjs_create_index" function, here is the correct syntax : <br/> <br/>
```hjs_init("absolute_directory_of_where_you_want_to_store_data")``` <br/>
```hjs_create_index()``` <br/> <br/>
These functions will create a file named "conf.json" in the same directory as the header and an "index.json" file in the storage folder.

### Hjs Functions
#### HJS Groups
HJS groups are sets of elements. These are the ones that will allow the data to be grouped together in order to hierarchise them.
<br/>To create a group, use the "hjs_create_group" function, with the following syntax : <br/> <br/>
```hjs_create_group("group_name")``` <br/> <br/>
To obtain a list of existing groups, use the "hjs_list_groups" function : <br/> <br/>
```hjs_list_groups()``` <br/> <br/>
To delete a group, use the "hjs_delete_group" function : <br/> <br/>
```hjs_delete_group("group_name")``` <br/> <br/>

#### HJS Elements
The elements of HJS are divided into groups, each element has a name, a type and a value. They can be string, int, bool, float, double. <br/> <br/>
To create an element, use the "hjs_create_element" function, with the following syntax : <br/> <br/>
```hjs_create_element("group_name", "element_name", "element_value", "element_type")``` <br/> <br/>
To obtain a list of existing elements, use the "hjs_list_elements" function : <br/> <br/>
```hjs_list_elements("group_name")``` <br/> <br/>
To delete an element, use the "hjs_delete_element" function : <br/> <br/>
```hjs_delete_element("group_name", "element_name")``` <br/> <br/>

#### Get element value and type
To get the type of an element, use the "hjs_get_element_type" function : <br/> <br/>
```hjs_get_element_type("group_name", "element_name")``` <br/> <br/>
This function will return a string containing the type of the element. <br/> <br/>
To get the value of an element, use the "hjs_get_element_value" function : <br/> <br/>
```hjs_get_<type of the element>_element("group_name", "element_name")``` <br/> <br/>