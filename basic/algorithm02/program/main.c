/*
 * ============================================
 *   영화 관리 프로그램 (동적 배열 기반)
 *   Dynamic Array-based Movie Manager in C
 * ============================================
 */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /* ── 상수 정의 ── */
#define TITLE_LEN    100
#define DIRECTOR_LEN  60
#define GENRE_LEN     30
#define INIT_CAPACITY  4   /* 초기 배열 용량 */

/* ── 영화 구조체 ── */
typedef struct {
    int    id;
    char   title[TITLE_LEN];
    char   director[DIRECTOR_LEN];
    char   genre[GENRE_LEN];
    int    year;
    double rating;   /* 0.0 ~ 10.0 */
} Movie;

/* ── 동적 배열 구조체 ── */
typedef struct {
    Movie* data;      /* 힙에 할당된 Movie 배열 */
    int    size;      /* 현재 저장된 영화 수     */
    int    capacity;  /* 현재 배열의 최대 용량   */
    int    nextId;    /* 자동 증가 ID           */
} MovieList;

/* ════════════════════════════════════════════
 *  동적 배열 기본 함수
 * ════════════════════════════════════════════ */

 /* 초기화 */
void list_init(MovieList* ml) {
    ml->data = (Movie*)malloc(sizeof(Movie) * INIT_CAPACITY);
    if (!ml->data) { perror("malloc"); exit(EXIT_FAILURE); }
    ml->size = 0;
    ml->capacity = INIT_CAPACITY;
    ml->nextId = 1;
}

/* 해제 */
void list_free(MovieList* ml) {
    free(ml->data);
    ml->data = NULL;
    ml->size = 0;
    ml->capacity = 0;
}

/* 용량이 부족하면 2배 확장 */
static void list_grow(MovieList* ml) {
    if (ml->size < ml->capacity) return;
    int newCap = ml->capacity * 2;
    Movie* tmp = (Movie*)realloc(ml->data, sizeof(Movie) * newCap);
    if (!tmp) { perror("realloc"); exit(EXIT_FAILURE); }
    ml->data = tmp;
    ml->capacity = newCap;
    printf("  [배열 확장: %d → %d 슬롯]\n", ml->capacity / 2, newCap);
}

/* ════════════════════════════════════════════
 *  CRUD 함수
 * ════════════════════════════════════════════ */

 /* 영화 추가 */
void movie_add(MovieList* ml,
    const char* title, const char* director,
    const char* genre, int year, double rating) {
    list_grow(ml);
    Movie* m = &ml->data[ml->size];
    m->id = ml->nextId++;
    strncpy(m->title, title, TITLE_LEN - 1);
    strncpy(m->director, director, DIRECTOR_LEN - 1);
    strncpy(m->genre, genre, GENRE_LEN - 1);
    m->title[TITLE_LEN - 1] = '\0';
    m->director[DIRECTOR_LEN - 1] = '\0';
    m->genre[GENRE_LEN - 1] = '\0';
    m->year = year;
    m->rating = rating;
    ml->size++;
    printf("  ✔ 등록 완료: [ID:%d] %s\n", m->id, m->title);
}

/* ID로 인덱스 찾기 (-1: 없음) */
static int find_index(const MovieList* ml, int id) {
    for (int i = 0; i < ml->size; i++)
        if (ml->data[i].id == id) return i;
    return -1;
}

/* 영화 수정 */
int movie_update(MovieList* ml, int id,
    const char* title, const char* director,
    const char* genre, int year, double rating) {
    int idx = find_index(ml, id);
    if (idx < 0) return 0;
    Movie* m = &ml->data[idx];
    strncpy(m->title, title, TITLE_LEN - 1);
    strncpy(m->director, director, DIRECTOR_LEN - 1);
    strncpy(m->genre, genre, GENRE_LEN - 1);
    m->title[TITLE_LEN - 1] = '\0';
    m->director[DIRECTOR_LEN - 1] = '\0';
    m->genre[GENRE_LEN - 1] = '\0';
    m->year = year;
    m->rating = rating;
    printf("  ✔ 수정 완료: [ID:%d] %s\n", id, m->title);
    return 1;
}

/* 영화 삭제 (swap-with-last 방식으로 O(1)) */
int movie_delete(MovieList* ml, int id) {
    int idx = find_index(ml, id);
    if (idx < 0) return 0;
    printf("  ✔ 삭제: [ID:%d] %s\n", id, ml->data[idx].title);
    ml->data[idx] = ml->data[ml->size - 1];  /* 마지막 요소로 덮어쓰기 */
    ml->size--;
    return 1;
}

/* ════════════════════════════════════════════
 *  검색 / 정렬 함수
 * ════════════════════════════════════════════ */

 /* 제목 부분 검색 */
void movie_search_title(const MovieList* ml, const char* keyword) {
    printf("\n  ── 제목 검색: \"%s\" ──\n", keyword);
    int found = 0;
    for (int i = 0; i < ml->size; i++) {
        if (strstr(ml->data[i].title, keyword)) {
            printf("  [ID:%d] %-30s │ %s │ %d │ %.1f\n",
                ml->data[i].id, ml->data[i].title,
                ml->data[i].genre, ml->data[i].year, ml->data[i].rating);
            found++;
        }
    }
    if (!found) printf("  검색 결과 없음.\n");
}

/* 장르 검색 */
void movie_search_genre(const MovieList* ml, const char* genre) {
    printf("\n  ── 장르 검색: \"%s\" ──\n", genre);
    int found = 0;
    for (int i = 0; i < ml->size; i++) {
        if (strcmp(ml->data[i].genre, genre) == 0) {
            printf("  [ID:%d] %-30s │ %d │ %.1f\n",
                ml->data[i].id, ml->data[i].title,
                ml->data[i].year, ml->data[i].rating);
            found++;
        }
    }
    if (!found) printf("  검색 결과 없음.\n");
}

/* qsort 비교 함수: 평점 내림차순 */
static int cmp_rating_desc(const void* a, const void* b) {
    double ra = ((const Movie*)a)->rating;
    double rb = ((const Movie*)b)->rating;
    return (ra < rb) - (ra > rb);   /* 내림차순 */
}

/* qsort 비교 함수: 연도 오름차순 */
static int cmp_year_asc(const void* a, const void* b) {
    return ((const Movie*)a)->year - ((const Movie*)b)->year;
}

/* 정렬 후 전체 출력 */
void movie_sort_and_print(MovieList* ml, int byRating) {
    if (ml->size == 0) { printf("  등록된 영화가 없습니다.\n"); return; }
    /* 임시 복사본에 정렬 적용 */
    Movie* tmp = (Movie*)malloc(sizeof(Movie) * ml->size);
    if (!tmp) { perror("malloc"); return; }
    memcpy(tmp, ml->data, sizeof(Movie) * ml->size);
    qsort(tmp, ml->size, sizeof(Movie),
        byRating ? cmp_rating_desc : cmp_year_asc);
    printf("\n  ┌─────┬──────────────────────────────┬────────────┬────────┬───────┬────────┐\n");
    printf("  │ ID  │ 제목                         │ 감독       │ 장르   │ 연도  │ 평점   │\n");
    printf("  ├─────┼──────────────────────────────┼────────────┼────────┼───────┼────────┤\n");
    for (int i = 0; i < ml->size; i++) {
        printf("  │ %-3d │ %-28s │ %-10s │ %-6s │ %-5d │  %4.1f  │\n",
            tmp[i].id, tmp[i].title,
            tmp[i].director, tmp[i].genre,
            tmp[i].year, tmp[i].rating);
    }
    printf("  └─────┴──────────────────────────────┴────────────┴────────┴───────┴────────┘\n");
    free(tmp);
}

/* 전체 목록 출력 (등록 순) */
void movie_print_all(const MovieList* ml) {
    printf("\n  ▶ 전체 영화 목록 (총 %d편, 배열 용량: %d)\n", ml->size, ml->capacity);
    if (ml->size == 0) { printf("  등록된 영화가 없습니다.\n"); return; }
    printf("  ┌─────┬──────────────────────────────┬────────────┬────────┬───────┬────────┐\n");
    printf("  │ ID  │ 제목                         │ 감독       │ 장르   │ 연도  │ 평점   │\n");
    printf("  ├─────┼──────────────────────────────┼────────────┼────────┼───────┼────────┤\n");
    for (int i = 0; i < ml->size; i++) {
        printf("  │ %-3d │ %-28s │ %-10s │ %-6s │ %-5d │  %4.1f  │\n",
            ml->data[i].id, ml->data[i].title,
            ml->data[i].director, ml->data[i].genre,
            ml->data[i].year, ml->data[i].rating);
    }
    printf("  └─────┴──────────────────────────────┴────────────┴────────┴───────┴────────┘\n");
}

/* ════════════════════════════════════════════
 *  파일 저장 / 불러오기
 * ════════════════════════════════════════════ */
#define SAVE_FILE "movies.dat"

void movie_save(const MovieList* ml) {
    FILE* fp = fopen(SAVE_FILE, "wb");
    if (!fp) { perror("fopen"); return; }
    fwrite(&ml->size, sizeof(int), 1, fp);
    fwrite(&ml->nextId, sizeof(int), 1, fp);
    fwrite(ml->data, sizeof(Movie), ml->size, fp);
    fclose(fp);
    printf("  ✔ %d편 저장 완료 → %s\n", ml->size, SAVE_FILE);
}

void movie_load(MovieList* ml) {
    FILE* fp = fopen(SAVE_FILE, "rb");
    if (!fp) { printf("  저장 파일 없음. 새로 시작합니다.\n"); return; }
    int size, nextId;
    fread(&size, sizeof(int), 1, fp);
    fread(&nextId, sizeof(int), 1, fp);
    /* 필요하면 용량 확장 */
    while (ml->capacity < size) list_grow(ml);
    fread(ml->data, sizeof(Movie), size, fp);
    ml->size = size;
    ml->nextId = nextId;
    fclose(fp);
    printf("  ✔ %d편 불러오기 완료 ← %s\n", size, SAVE_FILE);
}

/* ════════════════════════════════════════════
 *  입력 헬퍼
 * ════════════════════════════════════════════ */
static void flush_stdin(void) {
    int c; while ((c = getchar()) != '\n' && c != EOF);
}

static void read_str(const char* prompt, char* buf, int len) {
    printf("  %s", prompt);
    fgets(buf, len, stdin);
    buf[strcspn(buf, "\n")] = '\0';
}

static int read_int(const char* prompt) {
    int v; printf("  %s", prompt);
    scanf("%d", &v); flush_stdin(); return v;
}

static double read_double(const char* prompt) {
    double v; printf("  %s", prompt);
    scanf("%lf", &v); flush_stdin(); return v;
}

/* ════════════════════════════════════════════
 *  메인 메뉴
 * ════════════════════════════════════════════ */
static void print_menu(void) {
    printf("\n╔══════════════════════════════╗\n");
    printf("║      🎬  영화 관리 시스템      ║\n");
    printf("╠══════════════════════════════╣\n");
    printf("║  1. 영화 추가                 ║\n");
    printf("║  2. 전체 목록 보기            ║\n");
    printf("║  3. 영화 수정                 ║\n");
    printf("║  4. 영화 삭제                 ║\n");
    printf("║  5. 제목 검색                 ║\n");
    printf("║  6. 장르 검색                 ║\n");
    printf("║  7. 평점순 정렬               ║\n");
    printf("║  8. 연도순 정렬               ║\n");
    printf("║  9. 저장                      ║\n");
    printf("║  0. 종료                      ║\n");
    printf("╚══════════════════════════════╝\n");
    printf("  선택 >> ");
}

int main(void) {
    MovieList ml;
    list_init(&ml);
    movie_load(&ml);   /* 기존 데이터 불러오기 */

    /* 샘플 데이터: 목록이 비어있을 때만 삽입 */
    if (ml.size == 0) {
        movie_add(&ml, "기생충", "봉준호", "드라마", 2019, 8.5);
        movie_add(&ml, "인터스텔라", "놀란", "SF", 2014, 8.6);
        movie_add(&ml, "어벤져스", "루소", "액션", 2018, 8.4);
        movie_add(&ml, "라라랜드", "차젤", "뮤지컬", 2016, 8.0);
        movie_add(&ml, "매드맥스: 분노의 도로", "밀러", "액션", 2015, 8.1);
    }

    char title[TITLE_LEN], director[DIRECTOR_LEN], genre[GENRE_LEN];
    int  year, id, choice;

    while (1) {
        print_menu();
        scanf("%d", &choice); flush_stdin();

        switch (choice) {
        case 1:
            printf("\n  ── 영화 추가 ──\n");
            read_str("제목    : ", title, TITLE_LEN);
            read_str("감독    : ", director, DIRECTOR_LEN);
            read_str("장르    : ", genre, GENRE_LEN);
            year = read_int("개봉연도 : ");
            double rating = read_double("평점(0~10): ");
            movie_add(&ml, title, director, genre, year, rating);
            break;

        case 2:
            movie_print_all(&ml);
            break;

        case 3:
            movie_print_all(&ml);
            id = read_int("\n  수정할 ID: ");
            printf("\n  ── 새 정보 입력 ──\n");
            read_str("제목    : ", title, TITLE_LEN);
            read_str("감독    : ", director, DIRECTOR_LEN);
            read_str("장르    : ", genre, GENRE_LEN);
            year = read_int("개봉연도 : ");
            rating = read_double("평점(0~10): ");
            if (!movie_update(&ml, id, title, director, genre, year, rating))
                printf("  ✘ ID %d 를 찾을 수 없습니다.\n", id);
            break;

        case 4:
            movie_print_all(&ml);
            id = read_int("\n  삭제할 ID: ");
            if (!movie_delete(&ml, id))
                printf("  ✘ ID %d 를 찾을 수 없습니다.\n", id);
            break;

        case 5:
            read_str("\n  검색어(제목): ", title, TITLE_LEN);
            movie_search_title(&ml, title);
            break;

        case 6:
            read_str("\n  장르 입력: ", genre, GENRE_LEN);
            movie_search_genre(&ml, genre);
            break;

        case 7:
            printf("\n  ── 평점 높은 순 ──");
            movie_sort_and_print(&ml, 1);
            break;

        case 8:
            printf("\n  ── 개봉연도 오래된 순 ──");
            movie_sort_and_print(&ml, 0);
            break;

        case 9:
            movie_save(&ml);
            break;

        case 0:
            movie_save(&ml);
            list_free(&ml);
            printf("\n  프로그램을 종료합니다. 👋\n\n");
            return 0;

        default:
            printf("  잘못된 입력입니다.\n");
        }
    }
}