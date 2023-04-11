# hjs
A header library for storing and accessing hierarchical data for C++11, which uses the JSON structure. (Hierarchical JSON storage for C++).

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