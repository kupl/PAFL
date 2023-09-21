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

def print_performance():
    with open('my_example/_bug_info/example.json', 'r') as f:
        _bug_info = json.load(f)
    
    VERSIONS = 3
    METHODS = ["Ochiai","PAFL"]
    ranking_map = {}
    
    for method in METHODS:
        ranking_map[method] = []
        print("Method : {}".format(method))
        for idx in range(VERSIONS):
            #version
            ranking_map[method].append([])            
            version = idx + 1
            result_path = "coverage/{}-example#{}.json".format(method, version)
            with open(result_path, 'r') as f:
                result = json.load(f)
            #print(version)
            #print(_bug_info["version"])
            gt_file_line_list = _bug_info["version"][idx]
            for _, file_lines in enumerate(gt_file_line_list):
                file_name = file_lines["file"]
                lines = file_lines["lines"]
                for line in lines:
                    file_idx = result["files"].index(file_name)
                    result_list = result["lines"]
                    for _, my_result in enumerate(result_list):
                        if (my_result["index"] == file_idx) and (my_result["line"] == line):
                            print("Version : {}".format(version))
                            print("GT_line ranking : {}".format(my_result["ranking"]))
                            ranking_map[method][idx].append(my_result["ranking"])

    #For each method for each version for each GT ranking
    #ranking[method][version][ranking_list]
    print(ranking_map)                            
if __name__ == '__main__':
    # process
    process()
    # print ranking
    print_performance()
    




