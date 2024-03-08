#!bin/bash

bin/pafl -p example -l cpp -m ochiai,dstar,barinel -v 1-3 -d example/example -t example/test_example -i example/oracle --debug
bin/pafl -p example -l cpp -m ochiai,dstar,barinel -v 1-3 -d example/example -t example/test_example -i example/oracle --debug --pafl