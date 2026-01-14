Script chạy chương trình:

1. Biên dịch kplc
    - Mở WSL và chạy lệnh **make**

2. Chạy với các testcase
    - Chạy lệnh: 
        **./kplc tests/example1.kpl outputs/example1**
    - Làm tương tự với các testcase khác

3. So sánh kết quả với mẫu
    - Tiếp tục ở WSL chạy file run_tests.sh
        **bash run_tests.sh**
    - Kết quả sẽ hiện ra **PASS** nếu đúng, **FAIL** nếu sai