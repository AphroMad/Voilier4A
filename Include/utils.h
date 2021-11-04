/// Force la valeur du bit à 1
#define BIT_SET(var,offset) ((var) |= 0x1 << (offset))
/// Force la valeur du bit à 0
#define BIT_CLEAR(var,offset) ((var) &= ~(0x1 << (offset)))
/// Basculer le bit (0 -> 1 et 1 -> 0)
#define BIT_TOGGLE(var,offset) ((var) ^= 0x1 << (offset))
/// Vérifie si un bit est à 1 ou 0
// Le !! permet de forcer 1 pour "vrai" (et pas simplement != 0)
#define BIT_CHECK(var,offset) (!!((var) & (0x1 << (offset))))
#define BIT_SETV(var,offset,value) (BITMASK_SETV(var,0x1 << (offset), (value) << (offset)))

/// Force un masque à 1
#define BITMASK_SET(var,mask) ((var) |= (mask))
/// Force un masque à 0
#define BITMASK_CLEAR(var,mask) ((var) &= ~(mask))
/// Bascule tout un masque
#define BITMASK_TOGGLE(var,mask) ((var) ^= (mask))
/// Vérifie que tous les bits sont à 1, renvoie 1 ou 0
#define BITMASK_CHECK_ALL(var,mask) (!(~(var) & (mask)))
/// Vérifie que qu'au moins un bit du masque est à 1, renvoie la valeur masquée
#define BITMASK_CHECK_ANY(var,mask) ((var) & (mask))
/// Définie la valeur sous un masque
#define BITMASK_SETV(var,mask,value) ((var) = ((var) & ~(mask)) | (value))
/// Récupère la valeur contenue dans le masque
#define BITMASK_GET(var,mask) ((var) & (mask))

#define MAP(value,in_min,in_max,out_min,out_max) (((value) - (in_min)) * ((out_max) - (out_min)) / ((in_max) - (in_min)) + (out_min))
