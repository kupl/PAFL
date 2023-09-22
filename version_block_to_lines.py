import json
import os
import pickle


#DICT [FaultID] = version(int)
bugID_to_version = {}
tcID_to_int = {}



import json
import os

PATH = ""

#maps each block (str) to line numbers (int list) 
def block_to_path_fun_block_line(block_str):
    str_list = block_str.split(';', 1)
    path = str_list[0]
    fun_block_num_lines = str_list[1].split('@',1)[1]
    fun_line = fun_block_num_lines.split('#',1)[0]
    block_line = fun_block_num_lines.split('#',1)[1]
    block_line = block_line.split('$',1)[0]
    return (path, fun_line, block_line)

def get_end_line_pos(path):
    file_path = "{}/{}".format(PATH,path)
    myFile = open(file_path, 'r')
    #check
    endline = myFile.read().count("\n")
    return endline

def two_adj_block_strings_to_lines(block1, block2):
    #block 1
    print(block1)
    block1_triple = block_to_path_fun_block_line(block1)
    block1_path = block1_triple[0]
    block1_fun_line = int(block1_triple[1])
    block1_block_line = int(block1_triple[2])
    if block1_fun_line == block1_block_line - 1:
        block1_block_line = block1_block_line - 1
    print(block1_block_line)
    #block 2
    block2_triple = block_to_path_fun_block_line(block2)
    block2_path = block2_triple[0]
    block2_fun_line = int(block2_triple[1])
    block2_block_line = int(block2_triple[2])
    print(block2_block_line)
    #assume the blocks are sorted
    if (block1_path == block2_path) and (block1_fun_line == block2_fun_line):
        return [*range(block1_block_line, block2_block_line)]
    #same file different function
    elif (block1_path == block2_path) : # and (block1_fun_line != block2_fun_line)
        return [*range(block1_block_line, block2_block_line)]
    else:
        endline_pos = get_end_line_pos(block1_path)
        return [*range(block1_block_line, endline_pos)]


# def block_to_file(block_str):
#     str_list = block_str.split(';', 1)
#     file = str_list[0]
#     return file

# def process_tc_log_json():
#     version_tc_succ = {}
#     VERSIONS = 570
#     TC_NAME = "name"    
#     for version in range(VERSIONS):
#         version_tc_succ.append({})
#         version_tc_succ[version]
#     # write "version.test" file (passed or failed)
#     return version_tc_succ

# def process():
#     cmd = "mdir test_samsung"
#     os.system(cmd)

#     version_name_to_idx = {}
#     tc_name_to_idx = {}

#     sample_txt = "modules/math.c;namespace::fun_name@1#2$1"
#     path = sample_txt.split(';',1)
#     print(path)
    
#     process_tc_log_json()
    
    
if __name__ == '__main__':
    version_block_to_lines = {}
    
    
    sample_block1 = "modules/math.c;namespace::fun_name@1#2$1"
    sample_block2 = "modules/math.c;namespace::fun_name@1#4$2"
    print(two_adj_block_strings_to_lines(sample_block1, sample_block2))
    myFile = open("type.h", 'r')
    print(myFile.read().count("\n"))
    
