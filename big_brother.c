#include "big_brother.h"
#include "fat_volume.h"
#include "fat_table.h"
#include "fat_util.h"
#include <stdio.h>
#include <string.h>

#define LOG_FILE "/fs.log"

int bb_is_log_file_dentry(fat_dir_entry dir_entry) {
    return strncmp(LOG_FILE_BASENAME, (char *)(dir_entry->base_name), 3) == 0 &&
           strncmp(LOG_FILE_EXTENSION, (char *)(dir_entry->extension), 3) == 0;
}

int bb_is_log_filepath(char *filepath) {
    return strncmp(BB_LOG_FILE, filepath, 8) == 0;
}

int bb_is_log_dirpath(char *filepath) {
    return strncmp(BB_DIRNAME, filepath, 15) == 0;
}

/* Searches for a cluster that could correspond to the bb directory and returns
 * its index. If the cluster is not found, returns 0.
 */
u32 search_bb_orphan_dir_cluster() {
    //u32 bb_dir_start_cluster = 0;
    fat_volume vol = NULL;
    off_t offset = 0, cluster_off; 
    size_t bytes_to_read_cluster = 32;
    u32 cluster = 0;
    u8 *buf = alloca(sizeof(struct fat_dir_entry_s));
    vol = get_fat_volume();
    //fat_table_print(vol->table,0,1200);
    for (u32 bb_cluster = 0; bb_cluster < 10000; bb_cluster++)
    {
        cluster = fat_table_get_next_cluster(vol->table,bb_cluster);


        if (fat_table_cluster_is_bad_sector(cluster))
        {

            //offset in bytes of cluster
            cluster_off = fat_table_cluster_offset(vol->table, cluster) +
                      fat_table_mask_offset(offset, vol->table);
            // read bytes_to_read_cluster bytes
            full_pread(vol->table->fd, buf, bytes_to_read_cluster,
                                cluster_off);

            if (bb_is_log_file_dentry((fat_dir_entry)buf) == 0) {
              //DEBUG("ESTE ES EL CLUSTER --> %u", bb_cluster);
              return bb_cluster;
            }
        }        
    }
    return 0;
}


// /* Creates the /bb directory as an orphan and adds it to the file tree as 
//  * child of root dir.
//  */
// static int bb_create_new_orphan_dir(){
//     errno = 0;
    

        
//     // ****MOST IMPORTANT PART, DO NOT SAVE DIR ENTRY TO PARENT ****


//     return -errno;
// }


int bb_init_log_dir(u32 start_cluster) {
    errno = 0;
    fat_volume vol = NULL;
    fat_tree_node root_node = NULL;

    vol = get_fat_volume();

    // Create a new file from scratch, instead of using a direntry like normally done.
    fat_file loaded_bb_dir = fat_file_init_orphan_dir(BB_DIRNAME, vol->table, start_cluster);

    
    // Add directory to file tree. It's entries will be like any other dir.
    root_node = fat_tree_node_search(vol->file_tree, "/");
    vol->file_tree = fat_tree_insert(vol->file_tree, root_node, loaded_bb_dir);


    return -errno;
}
