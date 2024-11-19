


========================================
Issue: Lack of Boundary Checks
Type: BUFFER_OVERFLOW
File: drivers/gpu/drm/amd/amdgpu/si.c
Line: 1324

Description:
The function si_read_bios_from_rom lacks proper boundary checks when reading data into the bios buffer. The function calculates the number of dwords to read based on the input length_bytes, but it doesn't verify if this calculated length exceeds the actual allocated size of the bios buffer. This can lead to a buffer overflow, potentially causing memory corruption or security vulnerabilities.


========================================
============= reference diff =============
diff --git a/drivers/gpu/drm/amd/amdgpu/si.c b/drivers/gpu/drm/amd/amdgpu/si.c
index 8523547..c64b7ac 100644
--- a/drivers/gpu/drm/amd/amdgpu/si.c
+++ b/drivers/gpu/drm/amd/amdgpu/si.c
@@ -1319,6 +1319,8 @@ static bool si_read_bios_from_rom(struct amdgpu_device *adev,

        dw_ptr = (u32 *)bios;
        length_dw = ALIGN(length_bytes, 4) / 4;
+       if (length_dw * 4 > adev->bios_size)
+               return false;
        /* set rom index to 0 */
        WREG32(mmROM_INDEX, 0);
        for (i = 0; i < length_dw; i++)

========================================
============= generated diff =============
--- a/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/si.c
+++ b/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/si.c
@@ -1321,6 +1321,8 @@ static bool si_read_bios_from_rom(struct amdgpu_device *adev,
        length_dw = ALIGN(length_bytes, 4) / 4;
        /* set rom index to 0 */
        WREG32(mmROM_INDEX, 0);
+       if (length_dw * 4 > adev->bios_size)
+               return false;
        for (i = 0; i < length_dw; i++)
                dw_ptr[i] = RREG32(mmROM_DATA);

        return true;
========================================






========================================
Issue: Potential Buffer Overflow

CID: 1002
Severity: High
Type: Security
Category: Buffer Overflow
File: drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
Function: amdgpu_atombios_copy_swap
Line: 1627

Description:
The function amdgpu_atombios_copy_swap uses fixed-size buffers src_tmp and dst_tmp of 5 u32 elements (20 bytes) each. However, it processes num_bytes of data without checking if this exceeds the buffer size. This can lead to a buffer overflow if num_bytes is greater than 20.


========================================
============= reference diff =============
diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
index 0c8975ac5af9..300e5d19a9e6 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
@@ -1625,6 +1625,10 @@ void amdgpu_atombios_copy_swap(u8 *dst, u8 *src, u8 num_bytes, bool to_le)
        u32 src_tmp[5], dst_tmp[5];
        int i;
        u8 align_num_bytes = ALIGN(num_bytes, 4);
+       if (align_num_bytes > sizeof(src_tmp)) {
+        // Handle error: num_bytes too large
+        return;
+    }

        if (to_le) {
                memcpy(src_tmp, src, num_bytes);

========================================
============= generated diff =============
--- a/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
+++ b/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
@@ -1624,6 +1624,7 @@ static int amdgpu_atombios_copy_swap(struct amdgpu_atombios_dev *adev,
 {
        u32 src_tmp[5], dst_tmp[5];
        int i;
+       int buf_size = 20; // Total size of the buffer in bytes

        u8 align_num_bytes = ALIGN(num_bytes, 4);

@@ -1632,6 +1633,8 @@ static int amdgpu_atombios_copy_swap(struct amdgpu_atombios_dev *adev,
                memcpy(src_tmp, src, num_bytes);
                for (i = 0; i < align_num_bytes / 4; i++)
                        dst_tmp[i] = cpu_to_le32(src_tmp[i]);
+               if (num_bytes > buf_size)
+                       return -EINVAL;
                if (!to_le) {
                        for (i = 0; i < align_num_bytes / 4; i++)
                                dst[i] = cpu_to_le32(dst_tmp[i]);
========================================






========================================
Integer Overflow in amdgpu_atombios_copy_swap
CID: 2002

Severity: High
Type: Integer Overflow
File: drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
Line: 1627
Location: amdgpu_atombios_copy_swap function
Description
A potential integer overflow has been detected in the amdgpu_atombios_copy_swap function. The variable align_num_bytes, which is of type u8, is assigned the result of an ALIGN macro operation that can produce values greater than 255 for certain inputs of num_bytes.

u8 align_num_bytes = ALIGN(num_bytes, 4);


========================================
============= reference diff =============
diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
index 0c8975ac5af9..2bca21d8d043 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
@@ -1624,7 +1624,7 @@ void amdgpu_atombios_copy_swap(u8 *dst, u8 *src, u8 num_bytes, bool to_le)
 #ifdef __BIG_ENDIAN
        u32 src_tmp[5], dst_tmp[5];
        int i;
-       u8 align_num_bytes = ALIGN(num_bytes, 4);
+       u32 align_num_bytes = ALIGN(num_bytes, 4);

        if (to_le) {
                memcpy(src_tmp, src, num_bytes);

========================================
============= generated diff =============
diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
index bfd067e2d2f1..6419ab97d922 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
@@ -1624,7 +1624,7 @@ static int amdgpu_atombios_copy_swap(struct amdgpu_atombios_dev *adev,
 #ifdef __BIG_ENDIAN
        u32 src_tmp[5], dst_tmp[5];
        int i;
-       u8 align_num_bytes = ALIGN(num_bytes, 4);
+       u32 align_num_bytes = ALIGN(num_bytes, 4);

        if (to_le) {
                memcpy(src_tmp, src, num_bytes);
========================================






========================================
Type: Integer Overflow
File: drivers/gpu/drm/amd/amdgpu/amdgpu_bios.c
Function: amdgpu_read_bios_from_rom
Line: 177

Description:
An integer overflow vulnerability has been detected in the function amdgpu_read_bios_from_rom. The issue occurs when calculating the length of the BIOS to be allocated. The function uses the AMD_VBIOS_LENGTH macro to determine the initial length, then aligns it to 4 bytes using the ALIGN macro. This sequence of operations could potentially lead to an integer overflow, resulting in a smaller allocation than intended and possible buffer overflow when reading the BIOS.

========================================
============= reference diff =============
diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_bios.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_bios.c
index 42e64bce661e..428f93943093 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_bios.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_bios.c
@@ -156,7 +156,8 @@ bool amdgpu_read_bios(struct amdgpu_device *adev)
 static bool amdgpu_read_bios_from_rom(struct amdgpu_device *adev)
 {
        u8 header[AMD_VBIOS_SIGNATURE_END+1] = {0};
-       int len;
+       size_t len;
+       size_t aligned_len;

        if (!adev->asic_funcs || !adev->asic_funcs->read_bios_from_rom)
                return false;
@@ -174,7 +175,13 @@ static bool amdgpu_read_bios_from_rom(struct amdgpu_device *adev)

        /* valid vbios, go on */
        len = AMD_VBIOS_LENGTH(header);
-       len = ALIGN(len, 4);
+       if (len == 0 || len > MAX_BIOS_SIZE) {
+                       DRM_ERROR("Invalid BIOS length\n");
+                       return false;
+       }
+       aligned_len = ALIGN(len, 4);
+       if (aligned_len < len || aligned_len > MAX_BIOS_SIZE)
+                       return false;
        adev->bios = kmalloc(len, GFP_KERNEL);
        if (!adev->bios) {
                DRM_ERROR("no memory to allocate for BIOS\n");

========================================
============= generated diff =============
--- a/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/amdgpu_bios.c
+++ b/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/amdgpu_bios.c
@@ -174,7 +174,11 @@ static bool amdgpu_read_bios_from_rom(struct amdgpu_device *adev)
        return false;

        /* valid vbios, go on */
-       len = AMD_VBIOS_LENGTH(header);
+       unsigned int length = AMD_VBIOS_LENGTH(header);
+       if (length > AMD_VBIOS_MAX_LENGTH)
+               return false;
+       len = ALIGN(length, 4);
        adev->bios = kmalloc(len, GFP_KERNEL);
        if (!adev->bios) {
                DRM_ERROR("no memory to allocate for BIOS\n");
========================================






========================================
Type: BUFFER_OVERFLOW
File: drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c
Function: amdgpu_atif_verify_interface
Line: 256

Description: Potential buffer overflow in memcpy() operation

There is a potential buffer overflow in the call to memcpy(). The size argument
to memcpy() is derived from untrusted input (info->buffer.pointer) and may exceed
the size of the destination buffer.


========================================
============= reference diff =============
diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c
index f85ace0384d2..e653e060510e 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c
@@ -252,8 +252,11 @@ static int amdgpu_atif_verify_interface(struct amdgpu_atif *atif)
                goto out;
        }
        size = min(sizeof(output), size);
-
-       memcpy(&output, info->buffer.pointer, size);
+    size_t safe_size = min(sizeof(output), size);
+    if (safe_size > info->buffer.length) {
+        return -EINVAL;
+    }
+       memcpy(&output, info->buffer.pointer, safe_size);

        /* TODO: check version? */
        DRM_DEBUG_DRIVER("ATIF version %u\n", output.version);

========================================
============= generated diff =============
--- a/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c
+++ b/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c
@@ -253,7 +253,11 @@ static int amdgpu_atif_verify_interface(struct amdgpu_atif *atif,
        size = min(sizeof(output), size);

        memcpy(&output, info->buffer.pointer, size);

-       /* TODO: check version? */
+       size_t safe_size = min(sizeof(output), size);
+       if (safe_size > info->buffer.length) {
+               return -EINVAL;
+       }
+       memcpy(&output, info->buffer.pointer, safe_size);

        DRM_DEBUG_DRIVER("ATIF version %u\n", output.version);

        amdgpu_atif_parse_notification(&atif->notifications, output.notification_mask);
========================================






========================================
Issue: Null Pointer Dereference
File: drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
Function: amdgpu_cs_parser_init
Line: 51

Description:
The function 'amdgpu_cs_parser_init' dereferences 'cs' without first checking if it is NULL. This can lead to a null pointer dereference if 'cs' is NULL when the function is called.
Code Path:

Function 'amdgpu_cs_parser_init' is called with 'cs' as an argument
'cs' is dereferenced at line 51 without a NULL check: if (cs->in.num_chunks == 0)


========================================
============= reference diff =============
diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
index 1e475eb01417..d3db17084e3d 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
@@ -46,6 +46,8 @@ static int amdgpu_cs_parser_init(struct amdgpu_cs_parser *p,
                                 struct drm_file *filp,
                                 union drm_amdgpu_cs *cs)
 {
+       if (p == NULL || adev == NULL || filp == NULL || cs == NULL)
+               return -EINVAL;
        struct amdgpu_fpriv *fpriv = filp->driver_priv;

        if (cs->in.num_chunks == 0)

========================================
============= generated diff =============
--- a/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
+++ b/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
@@ -48,6 +48,8 @@ static int amdgpu_cs_parser_init(struct amdgpu_cs_parser *p,
                             struct drm_sched_entity *entity,
                             struct drm_sched_entity_group *group,
                             struct drm_file *filp,
-                            struct drm_amdgpu_cs *cs)
+                           struct drm_amdgpu_cs *cs)
+ {
+       if (!cs)
+           return -EINVAL;
        struct amdgpu_fpriv *fpriv = filp->driver_priv;

        if (cs->in.num_chunks == 0)
@@ -66,6 +68,8 @@ static int amdgpu_cs_parser_init(struct amdgpu_cs_parser *p,
        memset(p, 0, sizeof(*p));
        p->adev = adev;
        p->filp = filp;
+       p->cs = cs;
        return 0;
 }
========================================






========================================
Issue: Potential Buffer Overflow in sprintf

CID: 1001
Type: Buffer Overflow
Severity: High
File: drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
Line: 150

Description:
The function sprintf is used to write to the buffer stmp without any length checking. This could lead to a buffer overflow if the formatted string exceeds the size of stmp.


========================================
============= reference diff =============
diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
index 0c8975ac5af9..e215b5e2d183 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
@@ -147,7 +147,7 @@ void amdgpu_atombios_i2c_init(struct amdgpu_device *adev)
                        i2c = amdgpu_atombios_get_bus_rec_for_i2c_gpio(gpio);

                        if (i2c.valid) {
-                               sprintf(stmp, "0x%x", i2c.i2c_id);
+                               snprintf(stmp, sizeof(stmp), "0x%x", i2c.i2c_id);
                                adev->i2c_bus[i] = amdgpu_i2c_create(adev_to_drm(adev), &i2c, stmp);
                        }
                        gpio = (ATOM_GPIO_I2C_ASSIGMENT *)

========================================
============= generated diff =============
--- a/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
+++ b/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
@@ -147,7 +147,7 @@ static int amdgpu_atombios_i2c_init(struct amdgpu_device *adev)
                        i2c = amdgpu_atombios_get_bus_rec_for_i2c_gpio(gpio);

                        if (i2c.valid) {
-                               sprintf(stmp, "0x%x", i2c.i2c_id);
+                               snprintf(stmp, sizeof(stmp) "0x%x", i2c.i2c_id);
                                adev->i2c_bus[i] = amdgpu_i2c_create(adev_to_drm(adev), &i2c, stmp);
                        }
                        gpio = (ATOM_GPIO_I2C_ASSIGMENT *)
========================================






========================================
CID: 12345
Classification: NULL_RETURNS
Function: aldebaran_get_reset_handler
File: drivers/gpu/drm/amd/amdgpu/aldebaran.c
Line: 50

Description:
The function 'aldebaran_get_reset_handler' dereferences 'reset_ctl->handle' without first checking if 'reset_ctl' or 'reset_ctl->handle' is NULL. This could lead to a null pointer dereference if either 'reset_ctl' or 'reset_ctl->handle' is NULL when the function is called.

Execution path:
  1. Function aldebaran_get_reset_handler is called
  2. 'reset_ctl->handle' is dereferenced without a null check


========================================
============= reference diff =============
--- a/drivers/gpu/drm/amd/amdgpu/aldebaran.c
+++ b/drivers/gpu/drm/amd/amdgpu/aldebaran.c
@@ -46,11 +46,16 @@ aldebaran_get_reset_handler(struct amdgpu_reset_control *reset_ctl,
 			    struct amdgpu_reset_context *reset_context)
 {
 	struct amdgpu_reset_handler *handler;
-	struct amdgpu_device *adev = (struct amdgpu_device *)reset_ctl->handle;
+	struct amdgpu_device *adev;
 	int i;

+	if (!reset_ctl || !reset_ctl->handle) {
+		pr_err("Invalid reset control or handle\n");
+		return NULL;
+	}
+
+	adev = (struct amdgpu_device *)reset_ctl->handle;
+
 	if (reset_context->method == AMD_RESET_METHOD_NONE) {
 		if (aldebaran_is_mode2_default(reset_ctl))
 			reset_context->method = AMD_RESET_METHOD_MODE2;

========================================
============= generated diff =============
--- a/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/aldebaran.c
+++ b/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/aldebaran.c
@@ -47,7 +47,14 @@ aldebaran_get_reset_handler(struct amdgpu_reset_control *reset_ctl,
                             struct amdgpu_reset_context *reset_context)
 {
        struct amdgpu_reset_handler *handler;
-       struct amdgpu_device *adev = (struct amdgpu_device *)reset_ctl->handle;
+       struct amdgpu_device *adev;
+
+       if (!reset_ctl ||! reset_ctl->handle) {
+               pr_err("Invalid reset control or handle\n");
+               return NULL;
+       }
+
+       adev = (struct amdgpu_device *)reset_ctl->handle;
        int i;

        if (reset_context->method == AMD_RESET_METHOD_NONE) {
========================================






========================================
File: drivers/gpu/drm/amd/amdgpu/amdgpu_amdkfd_gpuvm.c

Line: 2469

Function: amdgpu_amdkfd_gpuvm_import_dmabuf_fd

Description: Use of freed memory:
 *mem may have been freed inside of import_obj_create.

Consider adding a check for NULL.

========================================
============= reference diff =============
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_amdkfd_gpuvm.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_amdkfd_gpuvm.c
@@ -2461,7 +2461,9 @@ int amdgpu_amdkfd_gpuvm_import_dmabuf_fd(struct amdgpu_device *adev, int fd,
        if (ret)
                goto err_put_obj;

-       (*mem)->gem_handle = handle;
+    if (*mem) {
+           (*mem)->gem_handle = handle;
+    }

        return 0;

========================================
============= generated diff =============
--- a/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/amdgpu_amdkfd_gpuvm.c
+++ b/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/amdgpu_amdkfd_gpuvm.c
@@ -2466,7 +2466,9 @@ static int amdgpu_amdkfd_gpuvm_import_dmabuf_fd(struct amdgpu_amdkfd_gpuvm *mem,
                mmap_offset);
        if (ret)
                goto err_put_obj;

-       (*mem)->gem_handle = handle;
+       if (*mem) {
+           (*mem)->gem_handle = handle;
+       }

        return 0;

err_put_obj:
========================================






========================================
Issue: Resource Leak
File: drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
Function: amdgpu_cs_pass1
Line: 218

Description:
A memory resource allocated using kvmalloc_array() may not be freed if an error occurs during execution.
The function amdgpu_cs_pass1 allocates memory for chunk_array using kvmalloc_array(). However, if an error occurs after this allocation but before the function successfully completes, the allocated memory may not be freed, resulting in a resource leak.


========================================
============= reference diff =============
diff --git a/drivers/gpu/drm/amd/amdgpu_cs.c b/drivers/gpu/drm/amd/amdgpu_cs.c
index af43fd5..6dfdff5 100644
--- a/drivers/gpu/drm/amd/amdgpu_cs.c
+++ b/drivers/gpu/drm/amd/amdgpu_cs.c
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
--- a/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
+++ b/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
@@ -215,6 +215,7 @@ static int amdgpu_cs_pass1(struct amdgpu_cs_parser *p,
                chunk_ptr = u64_to_user_ptr(chunk_array[i]);
                if (copy_from_user(&user_chunk, chunk_ptr,
                                   sizeof(struct drm_amdgpu_cs_chunk))) {
+                       i--;
                        ret = -EFAULT;
                        goto free_partial_kdata;
                }
========================================






========================================
Issue: Potential Memory Leak
File: drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
Line: 148

Description:
The function amdgpu_atpx_call allocates memory for buffer.pointer using ACPI_ALLOCATE_BUFFER, but does not free this memory in all code paths. Specifically, when the function succeeds (i.e., when acpi_evaluate_object does not fail), the allocated memory is returned to the caller without being freed.


========================================
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
--- a/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
+++ b/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
@@ -145,6 +145,10 @@ static int amdgpu_atpx_call(struct amdgpu_atpx_context *context,
        return NULL;
 }

+    if (!buffer.pointer) {
+               return NULL;
+       }
        return buffer.pointer;
 }
========================================






========================================
Issue: Potential Buffer Overflow in Wave Assignment Logging
Type: Buffer Overflow
File: drivers/gpu/drm/amd/amdgpu/gfx_v9_4_2.c
Line: 427

Description:
A potential buffer overflow has been detected in the function gfx_v9_4_2_log_wave_assignment(). The function uses a fixed-size buffer of 256 bytes to store a formatted string, but does not implement proper bounds checking. This could lead to a buffer overflow if the accumulated string length exceeds the allocated buffer size.

========================================
============= reference diff =============
diff --git a/drivers/gpu/drm/amd/amdgpu/gfx_v9_4_2.c b/drivers/gpu/drm/amd/amdgpu/gfx_v9_4_2.c
index 3f4fd2f..1f612a0 100644
--- a/drivers/gpu/drm/amd/amdgpu/gfx_v9_4_2.c
+++ b/drivers/gpu/drm/amd/amdgpu/gfx_v9_4_2.c
@@ -424,7 +424,9 @@ static void gfx_v9_4_2_log_wave_assignment(struct amdgpu_device *adev, uint32_t
        char *str;
        int size;

-       str = kmalloc(256, GFP_KERNEL);
+       int max_size = CU_ID_MAX * SIMD_ID_MAX * WAVE_ID_MAX * 64;
+
+       str = kmalloc(max_size, GFP_KERNEL);
        if (!str)
                return;

@@ -432,7 +434,7 @@ static void gfx_v9_4_2_log_wave_assignment(struct amdgpu_device *adev, uint32_t

        for (se = 0; se < adev->gfx.config.max_shader_engines; se++) {
                for (cu = 0; cu < CU_ID_MAX; cu++) {
-                       memset(str, 0, 256);
+                       memset(str, 0, max_size);
                        size = sprintf(str, "SE[%02d]CU[%02d]: ", se, cu);
                        for (simd = 0; simd < SIMD_ID_MAX; simd++) {
                                size += sprintf(str + size, "[");

========================================
============= generated diff =============
--- a/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/gfx_v9_4_2.c
+++ b/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/gfx_v9_4_2.c
@@ -424,7 +424,8 @@ void gfx_v9_4_2_log_wave_assignment(struct amdgpu_device *adev,
        char *str;
        int size;

-       str = kmalloc(256, GFP_KERNEL);
+       int max_buff_size = CU_ID_MAX * SIMD_ID_MAX * WAVE_ID_MAX * 64;
+       str = kmalloc(max_buff_size, GFP_KERNEL);
        if (!str)
                return;

@@ -432,7 +433,7 @@ void gfx_v9_4_2_log_wave_assignment(struct amdgpu_device *adev,

                for (se = 0; se < adev->gfx.config.max_shader_engines; se++)
                        for (cu = 0; cu < CU_ID_MAX; cu++) {
-                               memset(str, 0, 256);
+                               memset(str, 0, max_buff_size);
                                str_size = sprintf(str, "SE[%02d]CU[%02d]: ", se, cu);
                                for (simd = 0; simd < SIMD_ID_MAX; simd++) {
                                        str_size += sprintf(str + str_size, "[");
========================================






========================================
Type: Null pointer dereferences
File: drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
Function: amdgpu_gem_fault
Line: 50

Description:
  The function 'amdgpu_gem_fault' takes a pointer parameter 'vmf' of type 'struct vm_fault *'.
  This pointer and its member 'vma' are dereferenced (struct ttm_buffer_object *bo = vmf->vma->vm_private_data;) without first checking if they are null.
  If 'vmf' or 'vmf->vma' is null, this will result in a null pointer dereference.


========================================
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
--- a/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
+++ b/coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
@@ -47,6 +47,8 @@ static vm_fault_t amdgpu_gem_fault(struct vm_fault *vmf)
 static vm_fault_t amdgpu_gem_fault(struct vm_fault *vmf)
 {
        struct ttm_buffer_object *bo = vmf->vma->vm_private_data;
+       if (!vmf ||! vmf->vma)
+               return VM_FAULT_SIGSEGV;
        struct drm_device *ddev = bo->base.dev;
        vm_fault_t ret;
        int idx;
========================================


