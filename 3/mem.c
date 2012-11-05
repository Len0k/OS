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
		uefi_call_wrapper(systab->BootServices->FreePool, 1, md);
		return EFI_SUCCESS;
	}
	Print (L"Got memory map!\r\n");
	UINT64 total = 0;
	UINT64 totalEfiLoaderCode = 0,
		totalEfiLoaderData = 0,
		totalEfiBootServicesCode = 0,
		totalEfiBootServicesData = 0,
		totalEfiRuntimeServicesCode = 0,
		totalEfiRuntimeServicesData = 0,
		totalEfiConventionalMemory = 0,
		totalEfiUnusableMemory = 0,
		totalEfiACPIReclaimMemory = 0,
		totalEfiACPIMemoryNVS = 0,
		totalEfiMemoryMappedIO = 0,
		totalEfiMemoryMappedIOPortSpace = 0,
		totalEfiPalCode = 0,
		totalEfiMaxMemoryType = 0;
	UINT64 len = N/md_size;
	int i;
	for (i=0; i<len; ++i){
		switch (md[i].Type){
			case EfiLoaderCode:
				totalEfiLoaderCode += (md[i].NumberOfPages << 12);
				break;
			case EfiLoaderData:
				totalEfiLoaderData += (md[i].NumberOfPages << 12);
				break;
			case EfiBootServicesCode:
				totalEfiBootServicesCode += (md[i].NumberOfPages << 12);
				break;
			case EfiBootServicesData:
				totalEfiBootServicesData += (md[i].NumberOfPages << 12);
			        break;
			case EfiRuntimeServicesCode:
				totalEfiRuntimeServicesCode += (md[i].NumberOfPages << 12);
				break;
			case EfiRuntimeServicesData:
				totalEfiRuntimeServicesData += (md[i].NumberOfPages << 12);
			        break;
			case EfiConventionalMemory:
				totalEfiConventionalMemory += (md[i].NumberOfPages << 12);
				break;
			case EfiUnusableMemory:
				totalEfiUnusableMemory += (md[i].NumberOfPages << 12);
				break;
			case EfiACPIReclaimMemory:
 				totalEfiACPIReclaimMemory += (md[i].NumberOfPages << 12);
				break;
			case EfiACPIMemoryNVS:
				totalEfiACPIMemoryNVS += (md[i].NumberOfPages << 12);
				break;
			case EfiMemoryMappedIO:
				totalEfiMemoryMappedIO += (md[i].NumberOfPages << 12);
				break;
			case EfiMemoryMappedIOPortSpace:
				totalEfiMemoryMappedIOPortSpace += (md[i].NumberOfPages << 12);
				break;
			case EfiPalCode:
				totalEfiPalCode += (md[i].NumberOfPages << 12);
				break;
			case EfiMaxMemoryType:
				totalEfiMaxMemoryType += (md[i].NumberOfPages << 12);
		}
	}
	Print (L"Memory types sizes in Kilobytes:\n");
	Print(L"totalEfiLoaderCode = %d\n", totalEfiLoaderCode);
	Print(L"totalEfiLoaderData = %d\n", totalEfiLoaderData);
	Print(L"totalEfiBootServicesCode = %d\n", totalEfiBootServicesCode);
	Print(L"totalEfiBootServicesData = %d\n", totalEfiBootServicesData);
	Print(L"totalEfiRuntimeServicesCode = %d\n", totalEfiRuntimeServicesCode);
	Print(L"totalEfiRuntimeServicesData = %d\n", totalEfiRuntimeServicesData);
	Print(L"totalEfiConventionalMemory = %d\n", totalEfiConventionalMemory);
	Print(L"totalEfiUnusableMemory = %d\n", totalEfiUnusableMemory);
	Print(L"totalEfiACPIReclaimMemory = %d\n", totalEfiACPIReclaimMemory);
	Print(L"totalEfiACPIMemoryNVS = %d\n", totalEfiACPIMemoryNVS);
	Print(L"totalEfiMemoryMappedIO = %d\n", totalEfiMemoryMappedIO);
	Print(L"totalEfiMemoryMappedIOPortSpace = %d\n", totalEfiMemoryMappedIOPortSpace);
	Print(L"totalEfiPalCode = %d\n", totalEfiPalCode);
	Print(L"totalEfiMaxMemoryType = %d\n", totalEfiMaxMemoryType);

	uefi_call_wrapper(systab->BootServices->FreePool, 1, md);
	return EFI_SUCCESS;
}
