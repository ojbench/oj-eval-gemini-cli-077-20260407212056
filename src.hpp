#ifndef SRC_HPP
#define SRC_HPP

namespace sjtu {
    class CrossArray {
    private:
        int max_lines;
        int current_lines;
        int** arrays;
        int* sizes;

    public:
        explicit CrossArray(int lines) {
            max_lines = lines;
            current_lines = 0;
            if (max_lines > 0) {
                arrays = new int*[max_lines];
                sizes = new int[max_lines];
                for (int i = 0; i < max_lines; ++i) {
                    arrays[i] = nullptr;
                    sizes[i] = 0;
                }
            } else {
                arrays = nullptr;
                sizes = nullptr;
            }
        }

        CrossArray(const CrossArray & o) {
            max_lines = o.max_lines;
            current_lines = o.current_lines;
            if (max_lines > 0) {
                arrays = new int*[max_lines];
                sizes = new int[max_lines];
                for (int i = 0; i < max_lines; ++i) {
                    sizes[i] = o.sizes[i];
                    if (o.arrays[i] != nullptr) {
                        arrays[i] = new int[sizes[i]];
                        for (int j = 0; j < sizes[i]; ++j) {
                            arrays[i][j] = o.arrays[i][j];
                        }
                    } else {
                        arrays[i] = nullptr;
                    }
                }
            } else {
                arrays = nullptr;
                sizes = nullptr;
            }
        }

        CrossArray & WhichGreater(CrossArray & o) {
            int count_this = 0;
            for (int i = 0; i < current_lines; ++i) {
                count_this += sizes[i];
            }
            int count_o = 0;
            for (int i = 0; i < o.current_lines; ++i) {
                count_o += o.sizes[i];
            }
            if (count_o > count_this) {
                return o;
            }
            return *this;
        }

        bool IsSame(const CrossArray & o) {
            return this == &o;
        }

        bool InsertArrays(const int * Input, int size) {
            if (current_lines >= max_lines) {
                return false;
            }
            if (size > 0) {
                arrays[current_lines] = new int[size];
                for (int i = 0; i < size; ++i) {
                    arrays[current_lines][i] = Input[i];
                }
            } else {
                arrays[current_lines] = new int[0];
            }
            sizes[current_lines] = size;
            current_lines++;
            return true;
        }

        void AppendArrays(const int * Input, int Line, int size) {
            if (Line < 0 || Line >= current_lines) return;
            if (size <= 0) return;

            int old_size = sizes[Line];
            int new_size = old_size + size;
            int* new_array = new int[new_size];

            if (arrays[Line] != nullptr) {
                for (int i = 0; i < old_size; ++i) {
                    new_array[i] = arrays[Line][i];
                }
                delete[] arrays[Line];
            }
            
            for (int i = 0; i < size; ++i) {
                new_array[old_size + i] = Input[i];
            }

            arrays[Line] = new_array;
            sizes[Line] = new_size;
        }

        void DoubleCrossLength() {
            int new_max_lines = max_lines * 2;
            if (new_max_lines == 0) {
                // If max_lines was 0, doubling it is still 0.
                // But maybe we should allocate at least 1?
                // The problem says "翻倍", so 0 * 2 = 0.
            }
            
            int** new_arrays = nullptr;
            int* new_sizes = nullptr;

            if (new_max_lines > 0) {
                new_arrays = new int*[new_max_lines];
                new_sizes = new int[new_max_lines];

                for (int i = 0; i < max_lines; ++i) {
                    new_arrays[i] = arrays[i];
                    new_sizes[i] = sizes[i];
                }
                for (int i = max_lines; i < new_max_lines; ++i) {
                    new_arrays[i] = nullptr;
                    new_sizes[i] = 0;
                }
            }

            if (arrays != nullptr) delete[] arrays;
            if (sizes != nullptr) delete[] sizes;

            arrays = new_arrays;
            sizes = new_sizes;
            max_lines = new_max_lines;
        }

        const int * AtArray(int i) {
            if (i < 0 || i >= max_lines) return nullptr;
            return arrays[i];
        }

        int & At(int i, int j) {
            return arrays[i][j];
        }

        ~CrossArray() {
            if (arrays != nullptr) {
                for (int i = 0; i < max_lines; ++i) {
                    if (arrays[i] != nullptr) {
                        delete[] arrays[i];
                    }
                }
                delete[] arrays;
            }
            if (sizes != nullptr) {
                delete[] sizes;
            }
        }
    };
}

#endif // SRC_HPP
