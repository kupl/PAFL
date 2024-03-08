#!bin/bash

bin/pafl -p example -l cpp -v 1-3 -m ochiai,dstar,barinel -d ./example/example -t ./example/test_example -i ./example/oracle -g --pafl --debug