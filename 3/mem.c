#include <efi.h>
#include <efilib.h>

EFI_STATUS efi_main (EFI_HANDLE image, EFI_SYSTEM_TABLE *systab) {
	UINTN N = 0;
	EFI_MEMORY_DESCRIPTOR * md;
	UINTN md_size, md_key;
	UINT32 md_version;
	EFI_STATUS res;

	InitializeLib(image, systab);
	res = uefi_call_wrapper(systab->BootServices->GetMemoryMap, 5, &N, NULL, NULL, NULL, NULL);
	Print(L"Size required: %d\n\r", N);
	res = uefi_call_wrapper(systab->BootServices->AllocatePool, 3, EfiLoaderData, N, &md);
	if (res != EFI_SUCCESS){
		Print (L"Failed to allocate memory for memory map!\r\n");
		return EFI_SUCCESS;
	}
	res = uefi_call_wrapper(systab->BootServices->GetMemoryMap, 5, &N, md, &md_key, &md_size, &md_version);
	if (res != EFI_SUCCESS){
		Print (L"Error occured during GetMemoryMap: %d\r\n", res);
		Print (L"Size required: %d", N);
		return EFI_SUCCESS;
	}
	Print (L"Ok\r\n");
	return EFI_SUCCESS;
}
