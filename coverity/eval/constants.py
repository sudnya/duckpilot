LINES_BEFORE = 5
LINES_AFTER = 5
# 715a222ff40a17ccccccb61edbc973855c258c44043571cb52fde3f30fcd1231 - all input pb, including "Type: Null pointer dereferences\nFile: drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c
# 9a5bf45d30341298ffa107a31a692a2558c2d7e2645d951e4318efae5d58b2b0 - fits until Potential Buffer Overflow in Wave Assignment Logging
# b4b64c6202df87e405a710a891034e060ec80b77336276045dc46369551ce308 - fits until static union acpi_object *amdgpu_atpx_call(
# End of Oct 20th - sane model
# 9ea7f63b4865cb89ce8a27d8463f1021c03ce060b787043844b1f9cd5086dc67 -- everything overfits until "File: amdgpu_amdkfd_gpuvm.c\n\nLine: 2464"

# gold overfit "c7fbc6924bafd2885ea18a6e109126aecb44530d4cd0a3a0a016b83b3ebd4ce7"
