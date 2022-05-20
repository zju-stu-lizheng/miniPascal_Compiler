char courses[100][400];
int map[100];
int is_passed[100];
char course_name[5];

int main() {
    char ch;
    int num = 0;
    int index = 0;
    int total_credits = 0;
    int attempted_credits = 0;
    int passed_credits = 0;
    int remained_credits = 0;
    int total_score = 0;
    int field = 0;
    int credit = 0;
    int key = 0;
    int i = 0;
    double GPA = 0;
    int value = 0;
    int flag = 0;
    int j = 0;
    int k = 0;

    while(1) {
        scanf("%c", &ch);
        if(ch == '\n') {
            break;
        }
        index = 0;
        courses[num][index] = ch;
        ++index;
        while(1) {
            scanf("%c", &ch);
            if(ch == '\n') {
                break;
            }
            courses[num][index] = ch;
            ++index;
        }
        courses[num][index] = '\0';
        is_passed[num] = 0;
        ++num;
    }

    for(i = 0; i < num; ++i) {
        index = 0;
        field = 0;
        credit = 0;
        key = 0;
        while(courses[i][index] != '\0') {
            if(courses[i][index] == '|') {
                ++field;
                ++index;
            }
            if(field == 0) {
                if(courses[i][index] <= '9' && courses[i][index] >= '0') {
                    key = key * 10 + courses[i][index] - '0';
                }
                ++index;
            }
            else if(field == 1) {
                credit = courses[i][index] - '0';
                total_credits += credit;
                map[key] = i;
                ++index;
            }
            else if(field == 2) {
                if(courses[i][index] != '|') {
                    ++index;
                }
            }
            else if(field == 3) {
                if(courses[i][index] != '\0') {
                    if(courses[i][index] == 'A') {
                        attempted_credits += credit;
                        passed_credits += credit;
                        total_score = total_score + 4 * credit;
                        is_passed[i] = 1;
                    }
                    else if(courses[i][index] == 'B') {
                        attempted_credits += credit;
                        passed_credits += credit;
                        total_score = total_score + 3 * credit;
                        is_passed[i] = 1;
                    }
                    else if(courses[i][index] == 'C') {
                        attempted_credits += credit;
                        passed_credits += credit;
                        total_score = total_score + 2 * credit;
                        is_passed[i] = 1;
                    }
                    else if(courses[i][index] == 'D') {
                        attempted_credits += credit;
                        passed_credits += credit;
                        total_score = total_score + credit;
                        is_passed[i] = 1;
                    }
                    else if(courses[i][index] == 'F') {
                        attempted_credits += credit;
                    }
                }
                ++index;
            }
        }
    }

    if(attempted_credits != 0) {
        GPA = 1.0 * total_score / attempted_credits;
    }
    remained_credits = total_credits - passed_credits;
    printf("GPA: %.1lf\n", GPA);
    printf("Hours Attempted: %d\n", attempted_credits);
    printf("Hours Completed: %d\n", passed_credits);
    printf("Credits Remaining: %d\n", remained_credits);

    printf("\nPossible Courses to Take Next\n");
    if(remained_credits == 0) {
        printf("  None - Congratulations!\n");
    }
    else {
        value = 0;
        flag = 1;
        j = 0;
        for(i = 0; i < num; ++i) {
            // if(is_passed[i] == 1) {
            //     continue;
            // }
            if(is_passed[i] == 0) {
                index = 0;
                j = 0;
                while(courses[i][index] != '|') {
                    course_name[j] = courses[i][index];
                    ++j;
                    ++index;
                }
                course_name[j] = '\0';
                while(courses[i][++index] != '|');
                ++index;
                if(courses[i][index] == '|') {
                    printf("  ");
                    for(k = 0; k < j; ++k) {
                        printf("%c", course_name[k]);
                    }
                    printf("\n");
                    // printf("  %s\n", course_name);
                }
                else {
                    flag = 1;
                    key = 0;
                    while(courses[i][index] != '|') {
                        if(courses[i][index] <= '9' && courses[i][index] >= '0') {
                            key = key * 10 + courses[i][index] - '0';
                        }
                        else if(courses[i][index] == ',') {
                            value = map[key];
                            if(is_passed[value] == 0) {
                                flag = 0;
                            }
                            key = 0;
                        }
                        else if(courses[i][index] == ';') {
                            value = map[key];
                            if(is_passed[value] == 0) {
                                flag = 0;
                            }
                            key = 0;
                            if(flag == 1) {
                                break;
                            }
                            else {
                                flag = 1;
                            }
                        }
                        ++index;
                    }
                    if(courses[i][index] == '|') {
                        value = map[key];
                        if(is_passed[value] == 0) {
                            flag = 0;
                        }
                    }
                    if(flag == 1) {
                        printf("  ");
                        for(k = 0; k < j; ++k) {
                            printf("%c", course_name[k]);
                        }
                        printf("\n");
                        // printf("  %s\n", course_name);
                    }
                }
            }
        }
    }
    return 0;
}


