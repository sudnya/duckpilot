# Step 1: dataprep
 currently done manually

# Step 2: eval pipeline
`➜  coverity git:(sudnya.diff-pilot) ✗ ./eval/run.sh -i /app/duckpilot-coverity/dataset/input-perturbed-gold-test-set.jsonlines -m model_hash_here`

use the file that you want to run eval on. jsonlines format expected

# Step 3: visualize
`./visualize/run.sh -i /app/duckpilot-coverity/dataset/results.jsonlines`

diffs that will need to be manually inspected. #TODO: best open src tool to do this easily.

# Step 4: train
` ➜  coverity git:(sudnya.diff-pilot) ✗ ./train/run.sh -i /app/duckpilot-coverity/dataset/input-perturbed-gold-test-set.jsonlines`

use the file that contains all the examples that you'd like to fine tune the model on



----------
Notes:
-----------
1 out of the 4 input perturbations generates correct code, but messes up the + on the diff lines added.... rerunning sometimes solves the issue:


1. Example 1: 
`"bug_report_path": "amdgpu_atpx_handler-bug.txt", "bug_report_text": "Issue: Potential Memory Leak\nFile: drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c\nLine: 145`
```
============= reference diff =============

diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
index 375f02002579..0e717d89b3e7 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
@@ -144,7 +144,13 @@ static union acpi_object *amdgpu_atpx_call(acpi_handle handle, int function,
                kfree(buffer.pointer);
                return NULL;
        }
+   /* If status is AE_NOT_FOUND, buffer.pointer will be NULL */
+   if (!buffer.pointer) {
+       pr_warn("ATPX buffer is NULL\n");
+       return NULL;
+   }

+   /* Caller must free the returned buffer */
        return buffer.pointer;
 }



========================================

============= generated diff =============

diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
index 375f02002579..0e717d89b3e7 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
@@ -144,6 +144,8 @@ static union acpi_object *amdgpu_atpx_call(acpi_handle handle, int function,
                kfree(buffer.pointer);
                return NULL;
        }
+       /* If status is AE_NOT_FOUND, buffer.pointer will be NULL */
+       if (!buffer.pointer) {
                pr_warn("ATPX buffer is NULL\n");
                return NULL;
        }

@@ -152,7 +154,8 @@ static union acpi_object *amdgpu_atpx_call(acpi_handle handle, int function,
        return buffer.pointer;
 }
```

### another repro attempt:
```========================================

============= reference diff =============

diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
index 375f02002579..0e717d89b3e7 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
@@ -144,7 +144,13 @@ static union acpi_object *amdgpu_atpx_call(acpi_handle handle, int function,
                kfree(buffer.pointer);
                return NULL;
        }
+   /* If status is AE_NOT_FOUND, buffer.pointer will be NULL */
+   if (!buffer.pointer) {
+       pr_warn("ATPX buffer is NULL\n");
+       return NULL;
+   }

+   /* Caller must free the returned buffer */
        return buffer.pointer;
 }



========================================

============= generated diff =============

diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
index 8523547..c64b7ac 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
@@ -144,6 +144,8 @@ static union acpi_object *amdgpu_atpx_call(acpi_handle handle,
                kfree(buffer.pointer);
                return NULL;
        }
+   /* If status is AE_NOT_FOUND, buffer.pointer will be NULL */
+   if (!buffer.pointer) {
        pr_warn("ATPX buffer is NULL\n");
        return NULL;
    }

```

```========================================

============= reference diff =============

diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
index 375f02002579..0e717d89b3e7 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
@@ -144,7 +144,13 @@ static union acpi_object *amdgpu_atpx_call(acpi_handle handle, int function,
                kfree(buffer.pointer);
                return NULL;
        }
+   /* If status is AE_NOT_FOUND, buffer.pointer will be NULL */
+   if (!buffer.pointer) {
+       pr_warn("ATPX buffer is NULL\n");
+       return NULL;
+   }

+   /* Caller must free the returned buffer */
        return buffer.pointer;
 }



========================================

============= generated diff =============

diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
index 8523547..c64b7ac 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
@@ -144,6 +144,7 @@ static union acpi_object *amdgpu_atpx_call(acpi_handle handle, int function,
                kfree(buffer.pointer);
                return NULL;
        }
+   /* If status is AE_NOT_FOUND, buffer.pointer will be NULL */
        return buffer.pointer;
 }
</s>
```

2. `example 2: File: drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c\nFunction: amdgpu_gem_fault\nLine: 50`

```========================================

============= reference diff =============

diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
index 0e617dff8765..47521241ed06 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
@@ -47,7 +47,12 @@ static const struct drm_gem_object_funcs amdgpu_gem_object_funcs;

 static vm_fault_t amdgpu_gem_fault(struct vm_fault *vmf)
 {
+       if (!vmf || !vmf->vma)
+          return VM_FAULT_SIGSEGV;
+
        struct ttm_buffer_object *bo = vmf->vma->vm_private_data;
+       if (!bo)
+          return VM_FAULT_SIGSEGV;
        struct drm_device *ddev = bo->base.dev;
        vm_fault_t ret;
        int idx;



========================================

============= generated diff =============

--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
@@ -46,11 +46,16 @@ static const struct drm_gem_object_funcs amdgpu_gem_object_funcs;

 static vm_fault_t amdgpu_gem_fault(struct vm_fault *vmf)
 {
+       if (!vmf ||!vmf->vma)
+          return VM_FAULT_SIGSEGV;
        struct ttm_buffer_object *bo = vmf->vma->vm_private_data;
        struct drm_device *ddev = bo->base.dev;
        vm_fault_t ret;
        int idx;

        ret = ttm_bo_vm_reserve(bo, vmf);
+       if (ret!= 0)
+          return ret;
        return ret;
 };
</s>```


another repro attempt:
```========================================

============= reference diff =============

diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
index 0e617dff8765..47521241ed06 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
@@ -47,7 +47,12 @@ static const struct drm_gem_object_funcs amdgpu_gem_object_funcs;

 static vm_fault_t amdgpu_gem_fault(struct vm_fault *vmf)
 {
+       if (!vmf || !vmf->vma)
+          return VM_FAULT_SIGSEGV;
+
        struct ttm_buffer_object *bo = vmf->vma->vm_private_data;
+       if (!bo)
+          return VM_FAULT_SIGSEGV;
        struct drm_device *ddev = bo->base.dev;
        vm_fault_t ret;
        int idx;



========================================

============= generated diff =============

diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
index 8523547..c5e6e7d 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
@@ -47,6 +47,8 @@ static const struct drm_gem_object_funcs amdgpu_gem_object_funcs;

 static vm_fault_t amdgpu_gem_fault(struct vm_fault *vmf)
 {
+       if (!vmf ||!vmf->vma)
+               return VM_FAULT_SIGSEGV;
        struct ttm_buffer_object *bo = vmf->vma->vm_private_data;
        struct drm_device *ddev = bo->base.dev;
        vm_fault_t ret;
</s>```


```========================================

============= reference diff =============

diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
index 0e617dff8765..47521241ed06 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
@@ -47,7 +47,12 @@ static const struct drm_gem_object_funcs amdgpu_gem_object_funcs;

 static vm_fault_t amdgpu_gem_fault(struct vm_fault *vmf)
 {
+       if (!vmf || !vmf->vma)
+          return VM_FAULT_SIGSEGV;
+
        struct ttm_buffer_object *bo = vmf->vma->vm_private_data;
+       if (!bo)
+          return VM_FAULT_SIGSEGV;
        struct drm_device *ddev = bo->base.dev;
        vm_fault_t ret;
        int idx;



========================================

============= generated diff =============

--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
@@ -47,11 +47,16 @@ static const struct drm_gem_object_funcs amdgpu_gem_object_funcs;

 static vm_fault_t amdgpu_gem_fault(struct vm_fault *vmf)
 {
-       struct ttm_buffer_object *bo = vmf->vma->vm_private_data;
-       struct drm_device *ddev = bo->base.dev;
+    if (!vmf ||!vmf->vma) {
+        // Handle error, vmf or vmf->vma is null
+        return VM_FAULT_SIGSEGV;
+    }
+
+    struct ttm_buffer_object *bo = vmf->vma->vm_private_data;
+    struct drm_device *ddev = bo->base.dev;
        vm_fault_t ret;
        int idx;

        ret = ttm_bo_vm_reserve(bo, vmf);
</s>```

2. Example 3:
`"Issue: Resource Leak\nFile: drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c\nFunction: amdgpu_cs_pass1\nLine: 188`

```========================================

============= reference diff =============

diff --git a/data/raw-data/code/amdgpu_cs.c b/data/raw-data/code/amdgpu_cs.c
index af43fd5..6dfdff5 100644
--- a/data/raw-data/code/amdgpu_cs.c
+++ b/data/raw-data/code/amdgpu_cs.c
@@ -215,6 +215,7 @@ static int amdgpu_cs_pass1(struct amdgpu_cs_parser *p,
                if (copy_from_user(&user_chunk, chunk_ptr,
                                       sizeof(struct drm_amdgpu_cs_chunk))) {
                        ret = -EFAULT;
+                       i--;
                        goto free_partial_kdata;
                }
                p->chunks[i].chunk_id = user_chunk.chunk_id;



========================================

============= generated diff =============

diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
index 8523547..c64b7ac 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
@@ -215,6 +215,12 @@ static int amdgpu_cs_pass1(struct amdgpu_cs_parser *p,
                if (copy_from_user(&user_chunk, chunk_ptr,
                                       sizeof(struct drm_amdgpu_cs_chunk))) {
                        ret = -EFAULT;
+                       i--;
+                       if (i < 0)
+                          goto out;
                        goto free_partial_kdata;
                }
                p->chunks[i].chunk_id = user_chunk.chunk_id;
</s>```


More repro:
```========================================

============= reference diff =============

diff --git a/data/raw-data/code/amdgpu_cs.c b/data/raw-data/code/amdgpu_cs.c
index af43fd5..6dfdff5 100644
--- a/data/raw-data/code/amdgpu_cs.c
+++ b/data/raw-data/code/amdgpu_cs.c
@@ -215,6 +215,7 @@ static int amdgpu_cs_pass1(struct amdgpu_cs_parser *p,
                if (copy_from_user(&user_chunk, chunk_ptr,
                                       sizeof(struct drm_amdgpu_cs_chunk))) {
                        ret = -EFAULT;
+                       i--;
                        goto free_partial_kdata;
                }
                p->chunks[i].chunk_id = user_chunk.chunk_id;



========================================

============= generated diff =============

diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
index 8523547..c64b7ac 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
@@ -186,6 +186,7 @@ static int amdgpu_cs_pass1(struct amdgpu_cs_parser *p,
                if (!chunk_array)
                        return -ENOMEM;
        /* get chunks */
+       memset(chunk_array, 0, p->in.num_chunks * sizeof(uint64_t));
        for (i = 0; i < p->in.num_chunks; i++) {
                ret = amdgpu_cs_get_chunk(p->adev, p->in.chunk_array[i],
                                          &chunk_array[i]);
</s>```



```========================================

============= reference diff =============

diff --git a/data/raw-data/code/amdgpu_cs.c b/data/raw-data/code/amdgpu_cs.c
index af43fd5..6dfdff5 100644
--- a/data/raw-data/code/amdgpu_cs.c
+++ b/data/raw-data/code/amdgpu_cs.c
@@ -215,6 +215,7 @@ static int amdgpu_cs_pass1(struct amdgpu_cs_parser *p,
                if (copy_from_user(&user_chunk, chunk_ptr,
                                       sizeof(struct drm_amdgpu_cs_chunk))) {
                        ret = -EFAULT;
+                       i--;
                        goto free_partial_kdata;
                }
                p->chunks[i].chunk_id = user_chunk.chunk_id;



========================================

============= generated diff =============

diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
index 8523547..c64b7ac 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
@@ -186,6 +186,7 @@ static int amdgpu_cs_pass1(struct amdgpu_cs_parser *p,
                if (!chunk_array)
                        return -ENOMEM;
        /* get chunks */
+       p->chunk_num = i;
        for (i = 0; i < cs->in.num_chunks; i++)
                chunk_array[i] = amdgpu_cs_read_chunk(p, cs);
        return 0;
</s>```
