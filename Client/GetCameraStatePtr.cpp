// sub_180251D60 { client.dll + E8 ? ? ? ? 8B 48 78 }

__int64 __fastcall GetCameraStatePtr(__int64 base, int index)
{
  if ( index == -1 )
    return base + 24;
  else
    return base + 1672LL * index + 24;
}
