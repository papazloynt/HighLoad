## Functional testing
<details>
<summary>Result of functional testing</summary>
test_directory_index (__main__.HttpServer)
directory index file exists ... ok
test_document_root_escaping (__main__.HttpServer)
document root escaping forbidden ... ok
test_empty_request (__main__.HttpServer)
Send empty line ... ok
test_file_in_nested_folders (__main__.HttpServer)
file located in nested folders ... ok
test_file_not_found (__main__.HttpServer)
absent file returns 404 ... ok
test_file_type_css (__main__.HttpServer)
Content-Type for .css ... ok
test_file_type_gif (__main__.HttpServer)
Content-Type for .gif ... ok
test_file_type_html (__main__.HttpServer)
Content-Type for .html ... ok
test_file_type_jpeg (__main__.HttpServer)
Content-Type for .jpeg ... ok
test_file_type_jpg (__main__.HttpServer)
Content-Type for .jpg ... ok
test_file_type_js (__main__.HttpServer)
Content-Type for .js ... ok
test_file_type_png (__main__.HttpServer)
Content-Type for .png ... ok
test_file_type_swf (__main__.HttpServer)
Content-Type for .swf ... ok
test_file_urlencoded (__main__.HttpServer)
urlencoded filename ... ok
test_file_with_dot_in_name (__main__.HttpServer)
file with two dots in name ... ok
test_file_with_query_string (__main__.HttpServer)
query string with get params ... ok
test_file_with_slash_after_filename (__main__.HttpServer)
slash after filename ... ok
test_file_with_spaces (__main__.HttpServer)
filename with spaces ... ok
test_head_method (__main__.HttpServer)
head method support ... ok
test_index_not_found (__main__.HttpServer)
directory index file absent ... ok
test_large_file (__main__.HttpServer)
large file downloaded correctly ... ok
test_post_method (__main__.HttpServer)
post method forbidden ... ok
test_request_without_two_newlines (__main__.HttpServer)
Send GET without to newlines ... ok
test_server_header (__main__.HttpServer)
Server header exists ... ok

----------------------------------------------------------------------
Ran 24 tests in 0.123s

OK
</details>

### nginx 
ab -n 1000 -c 20 127.0.0.1:8082/httptest/wikipedia_russia.html
This is ApacheBench, Version 2.3 <$Revision: 1843412 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking 127.0.0.1 (be patient)
Completed 100 requests
Completed 200 requests
Completed 300 requests
Completed 400 requests
Completed 500 requests
Completed 600 requests
Completed 700 requests
Completed 800 requests
Completed 900 requests
Completed 1000 requests
Finished 1000 requests


Server Software:        nginx/1.23.2
Server Hostname:        127.0.0.1
Server Port:            8082

Document Path:          /httptest/wikipedia_russia.html
Document Length:        954824 bytes

Concurrency Level:      20
Time taken for tests:   0.512 seconds
Complete requests:      1000
Failed requests:        0
Total transferred:      955062000 bytes
HTML transferred:       954824000 bytes
Requests per second:    1954.25 [#/sec] (mean)
Time per request:       10.234 [ms] (mean)
Time per request:       0.512 [ms] (mean, across all concurrent requests)
Transfer rate:          1822682.82 [Kbytes/sec] received

Connection Times (ms)
min  mean[+/-sd] median   max
Connect:        0    0   0.3      0       4
Processing:     3   10   2.6      9      32
Waiting:        0    0   1.4      0      17
Total:          4   10   2.9     10      34

Percentage of the requests served within a certain time (ms)
50%     10
66%     10
75%     10
80%     10
90%     11
95%     12
98%     19
99%     30
100%     34 (longest request)


### c++

ab -n 1000 -c 20 127.0.0.1:8080/httptest/wikipedia_russia.html
This is ApacheBench, Version 2.3 <$Revision: 1843412 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking 127.0.0.1 (be patient)
Completed 100 requests
Completed 200 requests
Completed 300 requests
Completed 400 requests
Completed 500 requests
Completed 600 requests
Completed 700 requests
Completed 800 requests
Completed 900 requests
Completed 1000 requests
Finished 1000 requests


Server Software:        cool.chastikov
Server Hostname:        127.0.0.1
Server Port:            8080

Document Path:          /httptest/wikipedia_russia.html
Document Length:        954824 bytes

Concurrency Level:      20
Time taken for tests:   1.268 seconds
Complete requests:      1000
Failed requests:        0
Total transferred:      954972000 bytes
HTML transferred:       954824000 bytes
Requests per second:    788.90 [#/sec] (mean)
Time per request:       25.352 [ms] (mean)
Time per request:       1.268 [ms] (mean, across all concurrent requests)
Transfer rate:          735721.74 [Kbytes/sec] received

Connection Times (ms)
min  mean[+/-sd] median   max
Connect:        0    0   0.3      0       3
Processing:     3   25  10.5     24      61
Waiting:        1    6   4.6      5      27
Total:          3   25  10.6     25      61

Percentage of the requests served within a certain time (ms)
50%     25
66%     28
75%     31
80%     33
90%     39
95%     45
98%     49
99%     56
100%     61 (longest request)
