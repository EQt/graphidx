;;; Directory Local Variables
;;; For more information see (info "(emacs) Directory Variables")

((c++-mode
   (compile-command . "cd ../../build/ && make doctests -j$(nproc) && ./doctests -nc")
   (c-file-style . "stroustrup")))





