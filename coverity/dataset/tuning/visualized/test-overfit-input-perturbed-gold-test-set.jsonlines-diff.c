


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
</s>
========================================






========================================
**Issue:** Lack of Boundary Checks **Type:** BUFFER_OVERFLOW **File:** drivers/gpu/drm/amd/amdgpu/si.c **Line:** 1324

**Description:**
The `si_read_bios_from_rom` function neglects to validate the data transfer size, allowing the risk of exceeding the buffer's capacity and potentially causing a buffer overflow, which can lead to memory corruption or security breaches.
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
</s>
========================================






========================================
**Issue:** Lack of Boundary Checks **Type:** BUFFER_OVERFLOW **File:** drivers/gpu/drm/amd/amdgpu/si.c **Line:** 1324

**Description:**
The `si_read_bios_from_rom` function does not properly check the data transfer size against the allocated buffer size, leaving it vulnerable to buffer overflows that can result in memory corruption or security vulnerabilities.
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
</s>
========================================






========================================
**Issue:** Lack of Boundary Checks **Type:** BUFFER_OVERFLOW **File:** drivers/gpu/drm/amd/amdgpu/si.c **Line:** 1324

**Description:**
The `si_read_bios_from_rom` function fails to enforce a safeguard against excessive data transfer, allowing the possibility of a buffer overflow that can compromise system security and lead to memory corruption.
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
</s>
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
</s>
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
A potential integer overflow has been detected in the amdgpu_atombios_copy_swap function. The ALIGN macro operation can produce a value that exceeds the maximum capacity of the u8 variable align_num_bytes.


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
</s>
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
The amdgpu_atombios_copy_swap function is vulnerable to an integer overflow due to the assignment of the ALIGN macro result to the u8 variable align_num_bytes, which can lead to a value greater than 255 being stored in the variable.


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
</s>
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
A critical issue has been identified in the amdgpu_atombios_copy_swap function, where the ALIGN macro operation can produce an output that exceeds the maximum value that can be stored in the u8 variable align_num_bytes, potentially causing an integer overflow and resulting in unexpected behavior or data corruption.


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
</s>
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
</s>
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
The amdgpu_atombios_copy_swap function is vulnerable to an integer overflow due to the assignment of the ALIGN macro result to the u8 variable align_num_bytes, which can exceed its maximum capacity.

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
</s>
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
We've found a potential integer overflow issue in the amdgpu_atombios_copy_swap function. When the ALIGN macro is applied to num_bytes, the result can be too large to fit in the u8 variable align_num_bytes, which can cause problems.

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
</s>
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
A critical integer overflow vulnerability has been identified in the amdgpu_atombios_copy_swap function, where the ALIGN macro operation can produce an output that exceeds the maximum value that can be stored in the u8 variable align_num_bytes, potentially causing an integer overflow and resulting in unexpected behavior or data corruption.

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
</s>
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

        if (!adev->asic_funcs ||!adev->asic_funcs->read_bios_from_rom)
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
</s>
========================================






========================================
Type: Integer Overflow
File: drivers/gpu/drm/amd/amdgpu/amdgpu_bios.c
Function: amdgpu_read_bios_from_rom
Line: 177

Description:
An integer overflow vulnerability has been identified in the amdgpu_read_bios_from_rom function. The calculation of the BIOS length using the AMD_VBIOS_LENGTH macro and ALIGN macro can produce an overflow, resulting in an incorrect allocation size.

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

        if (!adev->asic_funcs ||!adev->asic_funcs->read_bios_from_rom)
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
</s>
========================================






========================================
Type: Integer Overflow
File: drivers/gpu/drm/amd/amdgpu/amdgpu_bios.c
Function: amdgpu_read_bios_from_rom
Line: 177

Description:
We've found a potential integer overflow issue in the amdgpu_read_bios_from_rom function. When calculating the BIOS length, the combination of the AMD_VBIOS_LENGTH macro and ALIGN macro can lead to an overflow, causing the function to allocate a smaller buffer than intended, which may result in a buffer overflow when reading the BIOS.

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

        if (!adev->asic_funcs ||!adev->asic_funcs->read_bios_from_rom)
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
</s>
========================================






========================================
Type: Integer Overflow
File: drivers/gpu/drm/amd/amdgpu/amdgpu_bios.c
Function: amdgpu_read_bios_from_rom
Line: 177

Description:
A critical integer overflow vulnerability has been identified in the amdgpu_read_bios_from_rom function, where the calculation of the BIOS length using the AMD_VBIOS_LENGTH macro and ALIGN macro can produce an output that exceeds the maximum value that can be stored in the allocated buffer, potentially resulting in a buffer overflow and data corruption when reading the BIOS.

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

        if (!adev->asic_funcs ||!adev->asic_funcs->read_bios_from_rom)
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
</s>
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
</s>
========================================






========================================
Type: BUFFER_OVERFLOW
File: drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c
Function: amdgpu_atif_verify_interface
Line: 256

Description: A potential buffer overflow vulnerability has been identified in the memcpy() operation. The size argument is derived from untrusted input, which may exceed the destination buffer size.


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
</s>
========================================






========================================
Type: BUFFER_OVERFLOW
File: drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c
Function: amdgpu_atif_verify_interface
Line: 256

Description: We've found a potential buffer overflow issue in the memcpy() call. The size of the copy is determined by untrusted input, which could be larger than the destination buffer, leading to a buffer overflow.


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
</s>
========================================






========================================
Type: BUFFER_OVERFLOW
File: drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c
Function: amdgpu_atif_verify_interface
Line: 256

Description: A critical buffer overflow vulnerability has been identified in the memcpy() operation, where the size argument is derived from untrusted input (info->buffer.pointer) and may exceed the size of the destination buffer, potentially leading to a buffer overflow and data corruption.


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
</s>
========================================






========================================
CID: 12345
Classification: NULL_RETURNS
Function: aldebaran_get_reset_handler
File: drivers/gpu/drm/amd/amdgpu/aldebaran.c
Line: 50

Description:
A null pointer dereference vulnerability exists in the function aldebaran_get_reset_handler, which fails to check if'reset_ctl' or'reset_ctl->handle' is null before accessing their contents. This can lead to a system crash or unexpected behavior if either pointer is null when the function is called.


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
--- a/drivers/gpu/drm/amd/amdgpu/aldebaran.c
+++ b/drivers/gpu/drm/amd/amdgpu/aldebaran.c
@@ -46,11 +46,16 @@ aldebaran_get_reset_handler(struct amdgpu_reset_control *reset_ctl,
 			    struct amdgpu_reset_context *reset_context)
 {
 	struct amdgpu_reset_handler *handler;
-	struct amdgpu_device *adev = (struct amdgpu_device *)reset_ctl->handle;
+	struct amdgpu_device *adev;
 	int i;

+	if (!reset_ctl ||!reset_ctl->handle) {
+		pr_err("Invalid reset control or handle\n");
+		return NULL;
+	}
+
+	adev = (struct amdgpu_device *)reset_ctl->handle;
+
 	if (reset_context->method == AMD_RESET_METHOD_NONE) {
 		if (aldebaran_is_mode2_default(reset_ctl))
 			reset_context->method = AMD_RESET_METHOD_MODE2;
</s>
========================================






========================================
CID: 12345
Classification: NULL_RETURNS
Function: aldebaran_get_reset_handler
File: drivers/gpu/drm/amd/amdgpu/aldebaran.c
Line: 50

Description:
The function aldebaran_get_reset_handler neglects to perform a null check on the'reset_ctl' and'reset_ctl->handle' pointers before accessing their contents. This can lead to a null pointer dereference if either pointer is null when the function is called, resulting in potential system crashes or data corruption.


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
--- a/drivers/gpu/drm/amd/amdgpu/aldebaran.c
+++ b/drivers/gpu/drm/amd/amdgpu/aldebaran.c
@@ -46,11 +46,16 @@ aldebaran_get_reset_handler(struct amdgpu_reset_control *reset_ctl,
 			    struct amdgpu_reset_context *reset_context)
 {
 	struct amdgpu_reset_handler *handler;
-	struct amdgpu_device *adev = (struct amdgpu_device *)reset_ctl->handle;
+	struct amdgpu_device *adev;
 	int i;

+	if (!reset_ctl ||!reset_ctl->handle) {
+		pr_err("Invalid reset control or handle\n");
+		return NULL;
+	}
+
+	adev = (struct amdgpu_device *)reset_ctl->handle;
+
 	if (reset_context->method == AMD_RESET_METHOD_NONE) {
 		if (aldebaran_is_mode2_default(reset_ctl))
 			reset_context->method = AMD_RESET_METHOD_MODE2;
</s>
========================================






========================================
File: amdgpu_amdkfd_gpuvm.c

Line: 2469

Function: amdgpu_amdkfd_gpuvm_import_dmabuf_fd

Description: Use of freed memory:
 *mem may have been freed inside of import_obj_create.

Consider adding a check for NULL.

========================================
============= reference diff =============
--- a/data/raw-data/code/amdgpu_amdkfd_gpuvm.c
+++ b/data/raw-data/code/amdgpu_amdkfd_gpuvm.c
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
--- a/data/raw-data/code/amdgpu_amdkfd_gpuvm.c
+++ b/data/raw-data/code/amdgpu_amdkfd_gpuvm.c
@@ -2461,7 +2461,9 @@ int amdgpu_amdkfd_gpuvm_import_dmabuf_fd(struct amdgpu_device *adev, int fd,
        if (ret)
                goto err_put_obj;

-       (*mem)->gem_handle = handle;
+    if (*mem) {
+           (*mem)->gem_handle = handle;
+    }

        return 0;
</s>
========================================






========================================
File: amdgpu_amdkfd_gpuvm.c

Line: 2469

Function: amdgpu_amdkfd_gpuvm_import_dmabuf_fd

Description:The function amdgpu_amdkfd_gpuvm_import_dmabuf_fd may access memory that has already been freed. Specifically, the '*mem' pointer may have been released in the import_obj_create function, leaving it pointing to invalid memory. To prevent potential crashes or data corruption, a null check should be added to ensure '*mem' is valid before accessing it.

========================================
============= reference diff =============
--- a/data/raw-data/code/amdgpu_amdkfd_gpuvm.c
+++ b/data/raw-data/code/amdgpu_amdkfd_gpuvm.c
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
--- a/data/raw-data/code/amdgpu_amdkfd_gpuvm.c
+++ b/data/raw-data/code/amdgpu_amdkfd_gpuvm.c
@@ -2461,7 +2461,9 @@ int amdgpu_amdkfd_gpuvm_import_dmabuf_fd(struct amdgpu_device *adev, int fd,
        if (ret)
                goto err_put_obj;

-       (*mem)->gem_handle = handle;
+    if (*mem) {
+           (*mem)->gem_handle = handle;
+    }

        return 0;
</s>
========================================






========================================
File: amdgpu_amdkfd_gpuvm.c

Line: 2469

Function: amdgpu_amdkfd_gpuvm_import_dmabuf_fd

Description: A potential use-after-free vulnerability exists in the function amdgpu_amdkfd_gpuvm_import_dmabuf_fd. The '*mem' pointer may be accessed after it has been freed in the import_obj_create function, leading to undefined behavior. To mitigate this issue, a null check should be added to verify that '*mem' is valid before accessing its contents.

========================================
============= reference diff =============
--- a/data/raw-data/code/amdgpu_amdkfd_gpuvm.c
+++ b/data/raw-data/code/amdgpu_amdkfd_gpuvm.c
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
--- a/data/raw-data/code/amdgpu_amdkfd_gpuvm.c
+++ b/data/raw-data/code/amdgpu_amdkfd_gpuvm.c
@@ -2461,7 +2461,9 @@ int amdgpu_amdkfd_gpuvm_import_dmabuf_fd(struct amdgpu_device *adev, int fd,
        if (ret)
                goto err_put_obj;

-       (*mem)->gem_handle = handle;
+    if (*mem) {
+           (*mem)->gem_handle = handle;
+    }

        return 0;
</s>
========================================






========================================
File: amdgpu_amdkfd_gpuvm.c

Line: 2469

Function: amdgpu_amdkfd_gpuvm_import_dmabuf_fd

Description: The function amdgpu_amdkfd_gpuvm_import_dmabuf_fd is at risk of accessing freed memory. The '*mem' pointer may be released in the import_obj_create function, leaving it pointing to invalid memory. To prevent potential crashes or data corruption, a null check should be added to ensure '*mem' is valid before accessing its contents.

========================================
============= reference diff =============
--- a/data/raw-data/code/amdgpu_amdkfd_gpuvm.c
+++ b/data/raw-data/code/amdgpu_amdkfd_gpuvm.c
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
--- a/data/raw-data/code/amdgpu_amdkfd_gpuvm.c
+++ b/data/raw-data/code/amdgpu_amdkfd_gpuvm.c
@@ -2461,7 +2461,9 @@ int amdgpu_amdkfd_gpuvm_import_dmabuf_fd(struct amdgpu_device *adev, int fd,
        if (ret)
                goto err_put_obj;

-       (*mem)->gem_handle = handle;
+    if (*mem) {
+           (*mem)->gem_handle = handle;
+    }

        return 0;
</s>
========================================






========================================
Issue: Resource Leak
File: drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
Function: amdgpu_cs_pass1
Line: 188

Description:
A memory resource allocated using kvmalloc_array() may not be freed if an error occurs during execution.
The function amdgpu_cs_pass1 allocates memory for chunk_array using kvmalloc_array(). However, if an error occurs after this allocation but before the function successfully completes, the allocated memory may not be freed, resulting in a resource leak.


========================================
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
</s>
========================================






========================================
Issue: Resource Leak
File: drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
Function: amdgpu_cs_pass1
Line: 188

Description:
The function amdgpu_cs_pass1 allocates memory for chunk_array using kvmalloc_array(), but fails to ensure its release in the event of an error. If an exception occurs after the allocation but before the function completes, the allocated memory may remain unfreed, leading to a resource leak.


========================================
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
</s>
========================================






========================================
Issue: Resource Leak
File: drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
Function: amdgpu_cs_pass1
Line: 188

Description:
A resource leak vulnerability exists in the function amdgpu_cs_pass1, which allocates memory for chunk_array using kvmalloc_array() but neglects to free it in the event of an error. This can result in memory being retained unnecessarily, leading to resource waste and potential system instability.


========================================
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
</s>
========================================






========================================
Issue: Resource Leak
File: drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
Function: amdgpu_cs_pass1
Line: 188

Description:
The function amdgpu_cs_pass1 allocates memory for chunk_array using kvmalloc_array(), but fails to properly handle the case where an error occurs after allocation but before the function completes. As a result, the allocated memory may not be released, leading to a memory leak and potential system resource exhaustion.


========================================
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
</s>
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
</s>
========================================






========================================
Issue: Null Pointer Dereference
File: drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
Function: amdgpu_cs_parser_init
Line: 51

Description:
The amdgpu_cs_parser_init function does not validate the 'cs' pointer before accessing its members. This can result in a null pointer dereference if 'cs' is null when the function is called, leading to a potential crash or unexpected behavior.
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
</s>
========================================






========================================
Issue: Null Pointer Dereference
File: drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
Function: amdgpu_cs_parser_init
Line: 51

Description:
A null pointer dereference vulnerability exists in the amdgpu_cs_parser_init function, which fails to check if the 'cs' pointer is valid before accessing its members. This can lead to a crash or unexpected behavior if 'cs' is null when the function is called.
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
</s>
========================================






========================================
Issue: Null Pointer Dereference
File: drivers/gpu/drm/amd/amdgpu/amdgpu_cs.c
Function: amdgpu_cs_parser_init
Line: 51

Description:
The amdgpu_cs_parser_init function is susceptible to a null pointer dereference if the 'cs' pointer is null when the function is called. This is because the function does not perform a null check before accessing the 'cs' pointer's members.
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
</s>
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
</s>
========================================






========================================
Issue: Potential Buffer Overflow in sprintf

CID: 1001
Type: Buffer Overflow
Severity: High
File: drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
Line: 150

Description:
The function sprintf is used to write to the buffer stmp without verifying the length of the formatted string. This can lead to a buffer overflow if the string exceeds the buffer's capacity, potentially causing data corruption or system instability.


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
</s>
========================================






========================================
Issue: Potential Buffer Overflow in sprintf

CID: 1001
Type: Buffer Overflow
Severity: High
File: drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
Line: 150

Description:
A buffer overflow vulnerability exists in the use of sprintf, which writes to the stmp buffer without checking the length of the formatted string. This can result in data being written beyond the buffer's bounds, potentially leading to system crashes or data corruption.


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
</s>
========================================






========================================
Issue: Potential Buffer Overflow in sprintf

CID: 1001
Type: Buffer Overflow
Severity: High
File: drivers/gpu/drm/amd/amdgpu/amdgpu_atombios.c
Line: 150

Description:
The function sprintf is used to write to the stmp buffer without ensuring that the formatted string fits within the buffer's capacity. This can lead to a buffer overflow, where data is written beyond the buffer's bounds, potentially causing system instability or data corruption.


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
</s>
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
--- a/drivers/gpu/drm/amd/amdgpu/aldebaran.c
+++ b/drivers/gpu/drm/amd/amdgpu/aldebaran.c
@@ -46,11 +46,16 @@ aldebaran_get_reset_handler(struct amdgpu_reset_control *reset_ctl,
 			    struct amdgpu_reset_context *reset_context)
 {
 	struct amdgpu_reset_handler *handler;
-	struct amdgpu_device *adev = (struct amdgpu_device *)reset_ctl->handle;
+	struct amdgpu_device *adev;
 	int i;

+	if (!reset_ctl ||!reset_ctl->handle) {
+		pr_err("Invalid reset control or handle\n");
+		return NULL;
+	}
+
+	adev = (struct amdgpu_device *)reset_ctl->handle;
+
 	if (reset_context->method == AMD_RESET_METHOD_NONE) {
 		if (aldebaran_is_mode2_default(reset_ctl))
 			reset_context->method = AMD_RESET_METHOD_MODE2;
</s>
========================================






========================================
CID: 12345
Classification: NULL_RETURNS
Function: aldebaran_get_reset_handler
File: drivers/gpu/drm/amd/amdgpu/aldebaran.c
Line: 50

Description:
The function aldebaran_get_reset_handler fails to validate the'reset_ctl' and'reset_ctl->handle' pointers before dereferencing them. This can lead to a null pointer dereference if either pointer is null when the function is called, resulting in potential system instability or crashes.


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
--- a/drivers/gpu/drm/amd/amdgpu/aldebaran.c
+++ b/drivers/gpu/drm/amd/amdgpu/aldebaran.c
@@ -46,11 +46,16 @@ aldebaran_get_reset_handler(struct amdgpu_reset_control *reset_ctl,
 			    struct amdgpu_reset_context *reset_context)
 {
 	struct amdgpu_reset_handler *handler;
-	struct amdgpu_device *adev = (struct amdgpu_device *)reset_ctl->handle;
+	struct amdgpu_device *adev;
 	int i;

+	if (!reset_ctl ||!reset_ctl->handle) {
+		pr_err("Invalid reset control or handle\n");
+		return NULL;
+	}
+
+	adev = (struct amdgpu_device *)reset_ctl->handle;
+
 	if (reset_context->method == AMD_RESET_METHOD_NONE) {
 		if (aldebaran_is_mode2_default(reset_ctl))
 			reset_context->method = AMD_RESET_METHOD_MODE2;
</s>
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
</s>
========================================






========================================
Issue: Potential Memory Leak
File: drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
Line: 148

Description:
The function amdgpu_atpx_call allocates memory for buffer.pointer using ACPI_ALLOCATE_BUFFER, but fails to release it in all scenarios. When the function succeeds, the allocated memory is returned to the caller without being freed, leading to a potential memory leak..


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
</s>
========================================






========================================
Issue: Potential Memory Leak
File: drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
Line: 148

Description:
A memory leak vulnerability exists in the function amdgpu_atpx_call, which allocates memory for buffer.pointer using ACPI_ALLOCATE_BUFFER but neglects to free it in all code paths. Specifically, when the function succeeds, the allocated memory is not released, resulting in a potential memory leak.


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
</s>
========================================






========================================
Issue: Potential Memory Leak
File: drivers/gpu/drm/amd/amdgpu/amdgpu_atpx_handler.c
Line: 148

Description:
The function amdgpu_atpx_call allocates memory for buffer.pointer using ACPI_ALLOCATE_BUFFER, but fails to properly handle memory deallocation in all cases. When the function succeeds, the allocated memory is not released, leading to a memory leak and potential system resource exhaustion.


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
</s>
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
diff --git a/data/raw-data/code/gfx_v9_4_2.c b/data/raw-data/code/gfx_v9_4_2.c
index 3f4fd2f..1f612a0 100644
--- a/data/raw-data/code/gfx_v9_4_2.c
+++ b/data/raw-data/code/gfx_v9_4_2.c
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
diff --git a/data/raw-data/code/gfx_v9_4_2.c b/data/raw-data/code/gfx_v9_4_2.c
index 3f4fd2f..1f612a0 100644
--- a/data/raw-data/code/gfx_v9_4_2.c
+++ b/data/raw-data/code/gfx_v9_4_2.c
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
</s>
========================================






========================================
Issue: Potential Buffer Overflow in Wave Assignment Logging
Type: Buffer Overflow
File: drivers/gpu/drm/amd/amdgpu/gfx_v9_4_2.c
Line: 427

Description:
The function gfx_v9_4_2_log_wave_assignment() uses a fixed-size buffer to store a formatted string, but lacks sufficient bounds checking. This can lead to a buffer overflow if the accumulated string length exceeds the allocated buffer size, potentially causing data corruption or system instability.

========================================
============= reference diff =============
diff --git a/data/raw-data/code/gfx_v9_4_2.c b/data/raw-data/code/gfx_v9_4_2.c
index 3f4fd2f..1f612a0 100644
--- a/data/raw-data/code/gfx_v9_4_2.c
+++ b/data/raw-data/code/gfx_v9_4_2.c
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
diff --git a/data/raw-data/code/gfx_v9_4_2.c b/data/raw-data/code/gfx_v9_4_2.c
index 3f4fd2f..1f612a0 100644
--- a/data/raw-data/code/gfx_v9_4_2.c
+++ b/data/raw-data/code/gfx_v9_4_2.c
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
</s>
========================================






========================================
Issue: Potential Buffer Overflow in Wave Assignment Logging
Type: Buffer Overflow
File: drivers/gpu/drm/amd/amdgpu/gfx_v9_4_2.c
Line: 427

Description:
A buffer overflow vulnerability exists in the function gfx_v9_4_2_log_wave_assignment(), which uses a fixed-size buffer to store a formatted string without implementing proper length checks. If the accumulated string length exceeds the buffer size, this can result in a buffer overflow, potentially leading to system crashes or data corruption.

========================================
============= reference diff =============
diff --git a/data/raw-data/code/gfx_v9_4_2.c b/data/raw-data/code/gfx_v9_4_2.c
index 3f4fd2f..1f612a0 100644
--- a/data/raw-data/code/gfx_v9_4_2.c
+++ b/data/raw-data/code/gfx_v9_4_2.c
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
diff --git a/data/raw-data/code/gfx_v9_4_2.c b/data/raw-data/code/gfx_v9_4_2.c
index 3f4fd2f..1f612a0 100644
--- a/data/raw-data/code/gfx_v9_4_2.c
+++ b/data/raw-data/code/gfx_v9_4_2.c
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
</s>
========================================






========================================
Issue: Potential Buffer Overflow in Wave Assignment Logging
Type: Buffer Overflow
File: drivers/gpu/drm/amd/amdgpu/gfx_v9_4_2.c
Line: 427

Description:
The function gfx_v9_4_2_log_wave_assignment() stores a formatted string in a fixed-size buffer, but fails to validate the string length before writing to the buffer. This can lead to a buffer overflow if the accumulated string length exceeds the allocated buffer size, resulting in potential data corruption or system instability.

========================================
============= reference diff =============
diff --git a/data/raw-data/code/gfx_v9_4_2.c b/data/raw-data/code/gfx_v9_4_2.c
index 3f4fd2f..1f612a0 100644
--- a/data/raw-data/code/gfx_v9_4_2.c
+++ b/data/raw-data/code/gfx_v9_4_2.c
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
diff --git a/data/raw-data/code/gfx_v9_4_2.c b/data/raw-data/code/gfx_v9_4_2.c
index 3f4fd2f..1f612a0 100644
--- a/data/raw-data/code/gfx_v9_4_2.c
+++ b/data/raw-data/code/gfx_v9_4_2.c
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
</s>
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
diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
index 0e617dff8765..47521241ed06 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
@@ -47,7 +47,12 @@ static const struct drm_gem_object_funcs amdgpu_gem_object_funcs;

 static vm_fault_t amdgpu_gem_fault(struct vm_fault *vmf)
 {
+       if (!vmf ||!vmf->vma)
+          return VM_FAULT_SIGSEGV;
+
        struct ttm_buffer_object *bo = vmf->vma->vm_private_data;
+       if (!bo)
+          return VM_FAULT_SIGSEGV;
        struct drm_device *ddev = bo->base.dev;
        vm_fault_t ret;
        int idx;
</s>
========================================






========================================
Type: Null pointer dereferences
File: drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
Function: amdgpu_gem_fault
Line: 50

Description:
 The function amdgpu_gem_fault accesses the 'vmf' pointer and its 'vma' member without verifying their validity. This can lead to a null pointer dereference if either 'vmf' or 'vmf->vma' is null, resulting in potential system crashes or instability.


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
diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
index 0e617dff8765..47521241ed06 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
@@ -47,7 +47,12 @@ static const struct drm_gem_object_funcs amdgpu_gem_object_funcs;

 static vm_fault_t amdgpu_gem_fault(struct vm_fault *vmf)
 {
+       if (!vmf ||!vmf->vma)
+          return VM_FAULT_SIGSEGV;
+
        struct ttm_buffer_object *bo = vmf->vma->vm_private_data;
+       if (!bo)
+          return VM_FAULT_SIGSEGV;
        struct drm_device *ddev = bo->base.dev;
        vm_fault_t ret;
        int idx;
</s>
========================================






========================================
Type: Null pointer dereferences
File: drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
Function: amdgpu_gem_fault
Line: 50

Description:
A null pointer dereference vulnerability exists in the function amdgpu_gem_fault, which fails to check the validity of the 'vmf' pointer and its 'vma' member before accessing them. If either 'vmf' or 'vmf->vma' is null, this can result in a null pointer dereference and potential system crashes.


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
diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
index 0e617dff8765..47521241ed06 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
@@ -47,7 +47,12 @@ static const struct drm_gem_object_funcs amdgpu_gem_object_funcs;

 static vm_fault_t amdgpu_gem_fault(struct vm_fault *vmf)
 {
+       if (!vmf ||!vmf->vma)
+          return VM_FAULT_SIGSEGV;
+
        struct ttm_buffer_object *bo = vmf->vma->vm_private_data;
+       if (!bo)
+          return VM_FAULT_SIGSEGV;
        struct drm_device *ddev = bo->base.dev;
        vm_fault_t ret;
        int idx;
</s>
========================================






========================================
Type: Null pointer dereferences
File: drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
Function: amdgpu_gem_fault
Line: 50

Description:
 The function amdgpu_gem_fault accesses the 'vmf' pointer and its 'vma' member without performing a null check. This can lead to a null pointer dereference if 'vmf' or 'vmf->vma' is null, resulting in potential system instability or crashes due to invalid memory access.


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
diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
index 0e617dff8765..47521241ed06 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
@@ -47,7 +47,12 @@ static const struct drm_gem_object_funcs amdgpu_gem_object_funcs;

 static vm_fault_t amdgpu_gem_fault(struct vm_fault *vmf)
 {
+       if (!vmf ||!vmf->vma)
+          return VM_FAULT_SIGSEGV;
+
        struct ttm_buffer_object *bo = vmf->vma->vm_private_data;
+       if (!bo)
+          return VM_FAULT_SIGSEGV;
        struct drm_device *ddev = bo->base.dev;
        vm_fault_t ret;
        int idx;
</s>
========================================






========================================
CID: 487621
Type: Buffer overflow
Severity: High
Checker: BUFFER_SIZE
Category: RISKY_PROGRAMMING_PRACTICE
File: drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c
Function: amdgpu_acpi_enumerate_xcc
Line: 1092

Problem:
Unbounded string operation using sprintf can cause buffer overflow

Abstract:
The code uses sprintf to write to buffer 'hid' without size checking. The sprintf 
operation could write beyond the buffer boundaries if the formatted output string 
exceeds the destination buffer size. This could corrupt adjacent memory and lead 
to system instability or security vulnerabilities.

Details:
The sprintf function is used to format a string containing "AMD" concatenated with 
a number. Since sprintf performs no bounds checking, if AMD_XCC_HID_START + id 
produces a large number, the resulting string could overflow the fixed-size 'hid' 
buffer. This occurs in the GPU driver's ACPI enumeration code which runs with 
kernel privileges.

Fix:
Replace sprintf with snprintf and specify the buffer size:
  snprintf(hid, sizeof(hid), "%s%d", "AMD", AMD_XCC_HID_START + id)

========================================
============= reference diff =============
diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c
index f85ace0384d2..10dfa3a37333 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c
@@ -1089,7 +1089,7 @@ static int amdgpu_acpi_enumerate_xcc(void)
        xa_init(&numa_info_xa);

        for (id = 0; id < AMD_XCC_MAX_HID; id++) {
-               sprintf(hid, "%s%d", "AMD", AMD_XCC_HID_START + id);
+               snprintf(hid, sizeof(hid), "%s%d", "AMD", AMD_XCC_HID_START + id);
                acpi_dev = acpi_dev_get_first_match_dev(hid, NULL, -1);
                /* These ACPI objects are expected to be in sequential order. If
                 * one is not found, no need to check the rest.
========================================
============= generated diff =============
diff --git a/drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c b/drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c
index f85ace0384d2..10dfa3a37333 100644
--- a/drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c
+++ b/drivers/gpu/drm/amd/amdgpu/amdgpu_acpi.c
@@ -1089,7 +1089,7 @@ static int amdgpu_acpi_enumerate_xcc(void)
        xa_init(&numa_info_xa);

        for (id = 0; id < AMD_XCC_MAX_HID; id++) {
-               sprintf(hid, "%s%d", "AMD", AMD_XCC_HID_START + id);
+               snprintf(hid, sizeof(hid), "%s%d", "AMD", AMD_XCC_HID_START + id);
                acpi_dev = acpi_dev_get_first_match_dev(hid, NULL, -1);
                /* These ACPI objects are expected to be in sequential order. If
                 * one is not found, no need to check the rest.</s>
========================================



