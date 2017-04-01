#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lib/brute.h"
#include "lib/kmp.h"
#include "lib/shiftand.h"
#include "lib/bmhs.h"

int main() {
    int brute, kmp, bmhs,
        sand, fsand;
    float start, end;
    float times[5];

    Text p = make_text("odio posuere", 0);
    Text t = make_text("Duis placerat viverra arcu sed sodales. Sed vel congue tortor.  Suspendisse potenti. Nam fringilla magna lacus, hendrerit tempus ex ornare vitae. Duis ullamcorper at dolor ac hendrerit. Sed mattis tortor nisl, ut consequat ex dignissim et. Curabitur venenatis consequat accumsan. Phasellus eu tortor luctus, viverra libero nec, tincidunt odio. Suspendisse est tortor, posuere sit amet dui vitae, elementum lacinia diam. Phasellus hendrerit risus sed nisi dictum efficitur. Nulla eget laoreet massa, sed fermentum tortor. Sed et urna quis diam pellentesque tempor. Praesent dignissim ex vel egestas cursus.  Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Morbi et est molestie, porta tortor eget, accumsan urna. Sed eros lorem, fermentum nec ornare nec, congue et metus. Vivamus eget laoreet mi, ac ultrices dolor. Pellentesque in laoreet tortor, eu vulputate neque. Vivamus tempus dictum lectus, eget porta purus pretium a. Vestibulum pellentesque elit at euismod porta. Donec id neque tincidunt, elementum massa ut, imperdiet ex. Proin cursus tincidunt erat, in condimentum leo hendrerit ac. Ut placerat lorem nibh, vel placerat lectus tincidunt vitae. Donec sed massa consequat, sodales ex in, varius metus. Nam pharetra accumsan nunc non tristique. Aenean porta eros at augue mollis tempor. Etiam nibh quam, aliquet dictum eros finibus, consectetur suscipit leo. Pellentesque porta mauris id erat vestibulum, nec euismod odio posuere.", 0);
    MaskTable mtbl = make_mask_table(p);
    NTable dtbl = make_delta_table(p);
    NTable ptbl = make_prefix_table(p);

    start = (float)clock()/CLOCKS_PER_SEC;
    brute = brute_search(t, p);
    end = (float)clock()/CLOCKS_PER_SEC;
    times[0] = end - start;

    start = (float)clock()/CLOCKS_PER_SEC;
    kmp = kmp_search(t, p, ptbl);
    end = (float)clock()/CLOCKS_PER_SEC;
    times[1] = end - start;

    start = (float)clock()/CLOCKS_PER_SEC;
    bmhs = bmhs_search(t, p, dtbl);
    end = (float)clock()/CLOCKS_PER_SEC;
    times[2] = end - start;

    start = (float)clock()/CLOCKS_PER_SEC;
    sand = shift_and_search(t, p, mtbl);
    end = (float)clock()/CLOCKS_PER_SEC;
    times[3] = end - start;


    unsigned k = 1;
    start = (float)clock()/CLOCKS_PER_SEC;
    fsand = shift_and_fuzzy(t, p, mtbl, k);
    end = (float)clock()/CLOCKS_PER_SEC;
    times[4] = end - start;

    printf(
        "Pattern [%s]\n\n"
        "Brute: %i (%f)\n"
        "KMP: %i (%fs)\n"
        "BMHS: %i (%fs)\n"
        "Shift-And: %i (%fs)\n"
        "Fuzzy Shift-And (k=%u): %i (%fs)\n",
        p.val,
        brute, times[0],
        kmp, times[1],
        bmhs, times[2],
        sand, times[3],
        k, fsand, times[4]
    );

    free_text(&p);
    free_text(&t);

    return 0;
}
