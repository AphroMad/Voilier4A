#ifndef GPIO_H
#define GPIO_H

#include <stm32f10x.h>
#include <utils.h>

/*!
 * Tous les modes disponibles pour un pin
 *
 * Attention, certains modes comme GPIO_MODE_OUT_ALT_PUSH_PULL doivent être initialisé en même temps qu'un autre périphérique (un timer pour un pwm par exemple)
 */
enum GPIO_Mode {
	GPIO_MODE_IN_FLOATING = 0, ///< Pin en mode entrée flotante
	GPIO_MODE_IN_PULL_UP = 1, ///< Pin en mode entrée forcée à 3.3V
	GPIO_MODE_IN_PULL_DOWN = 2, ///< Pin en mode entrée forcée à 0V
	GPIO_MODE_IN_ANALOG = 3, ///< Pin en mode entrée analogique
	GPIO_MODE_OUT_OPEN_DRAIN = 4, ///< Pin en mode sortie "open drain" (seul l'état 0V est forcé)
	GPIO_MODE_OUT_PUSH_PULL = 5, ///< Pin en mode sortie "push/pull" (~forcé à l'état haut/bas)
	GPIO_MODE_OUT_ALT_OPEN_DRAIN = 6, ///< Pin en mode sortie alternative "open drain", utilisé pour le PWM
	GPIO_MODE_OUT_ALT_PUSH_PULL = 7, ///< Pin en mode sortie alternative "push/pull", utilisé pour le PWM
};

/*!
 * Tous les modes d'interruption possibles
 */
enum GPIO_Interrupt_Mode {
	GPIO_INTERRUPT_MODE_RISING = 0, ///< Interruption sur un front montant
	GPIO_INTERRUPT_MODE_FALLING = 1, ///< Interruption sur un front descendant
	GPIO_INTERRUPT_MODE_BOTH = 2, ///< Interruption sur tous les fronts
};

/*!
 * Correspondance entre un GPIO_Mode et la configuration des registres
 */
extern const uint8_t GPIO_Mode_Conf[8];

/*!
 * Structure présentant les différents paramètres pour un pin, utilisé en tant que premier argument des fonctions GPIO_*
 */
struct GPIO {
	GPIO_TypeDef *gpio; ///< Adresse du GPIO assocé
	uint8_t pin; ///< Numéro du pin
	enum GPIO_Mode mode; ///< Mode du pin
};


/*!
 * Initialisation d'un GPIO
 *
 * Attention, certains GPIO sont relié à des périphériques spécifiques qui ont également besoin d'être initialisés
 */
void GPIO_Init(struct GPIO *gpio);

/*!
 * Définition de la valeur d'un GPIO
 */
void GPIO_Set(struct GPIO *gpio, uint8_t level);

/*!
 * Définition d'une interruption pour un GPIO
 * 
 * Attention, il n'y a que 5 interruptions différentes et elles fonctionnent par bloc (il n'est possible d'en détecter qu'une par ligne):
 *   - PA0/PB0/PC0/PD0/PE0
 *   - PA1/PB1/PC1/PD1/PE1
 *   - PA2/PB2/PC2/PD2/PE2
 *   - PA3/PB3/PC3/PD3/PE3
 *   - PA4/PB4/PC4/PD4/PE4
 */
void GPIO_Attach_Interrupt(struct GPIO* gpio, void (*interrupt)(void), uint8_t priority, enum GPIO_Interrupt_Mode mode);

#endif // GPIO_H
