import json
import os


def process_dir():
    PATH = "/home/minseok/PAFL"
    folder_list = []
    files = os.listdir("/home/minseok/PAFL")
    for _, file in enumerate(files):
        path = "{}/{}".format(PATH,file)
        if os.path.isdir(path):
            folder_list.append(file)
    
    print(folder_list)
 

def process():
    with open('my_example/_bug_info/example.json', 'r') as f:
        json_data = json.load(f)
    
    _bug_info = {}
    _bug_info["version"] = []
    
    VERSIONS = 3
    
    
    for version in range(VERSIONS):
    
        #buggy lines of file for version : version
        _bug_info["version"].append([])
    
    
        #process each buggy file of in buggy files of a version
        for file_name in ["example.c"]:
        
          #process a buggy file
          GT_lines_per_file = {}
    
          # GT file name of a version
          GT_lines_per_file["file"] = file_name
    
          #process buggy line for the file
          GT_lines_per_file["lines"] = []
          GT_lines_per_file["lines"].append(4)
          _bug_info["version"][version].append(GT_lines_per_file)
    
    
    print(json_data["version"])
    print(_bug_info["version"])
    process_dir()
    with open('example.json','w') as f:
        json.dump(_bug_info, f, ensure_ascii=False, indent=4)


if __name__ == '__main__':
    process()

