
/*
 * Logwarn - Utility for finding interesting messages in log files
 *
 * Copyright (C) 2010-2011 Archie L. Cobbs. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Maximum line length
#define MAX_LINE_LENGTH     100000

// Pattern repeat state
struct repeat {
    unsigned int    hash;           // xor of hashes of pattern string(s)
    unsigned int    num;            // number required in interval
    unsigned int    secs;           // interval duration in seconds
    unsigned long   *occurrences;   // timestamps of up to `num' occurrences, most recent first
};

// Log scan state
struct scan_state {
    ino_t           inode;          // file inode number
    unsigned long   line;           // # lines read + 1
    long            pos;            // seek position in file
    unsigned char   matching;       // within matching entry
    unsigned int    num_repeats;    // number of repeats
    struct repeat   *repeats;       // repeat state
};

// Exit values
#define EXIT_OK             0
#define EXIT_MATCHES        1
#define EXIT_ERROR          2

// Global variables
extern const char *const logwarn_version;

// Global functions
extern void reset_state(struct scan_state *state);
extern int  load_state(const char *state_file, struct scan_state *state);
extern void save_state(const char *state_file, const char *logfile, const struct scan_state *state);
extern void dump_state(FILE *fp, const char *logfile, const struct scan_state *state);
extern void init_state_from_logfile(const char *logfile, struct scan_state *state);
extern void state_file_name(const char *state_dir, const char *logfile, char *buf, size_t max);
extern struct repeat *find_repeat(struct scan_state *state, unsigned int hash);

