/**
* @file
* @ingroup qs
* @brief Internal (package scope) QS/C interface.
* @cond
******************************************************************************
* Last updated for version 6.7.0
* Last updated on  2019-12-17
*
*                    Q u a n t u m  L e a P s
*                    ------------------------
*                    Modern Embedded Software
*
* Copyright (C) 2005-2019 Quantum Leaps, LLC. All rights reserved.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Alternatively, this program may be distributed and modified under the
* terms of Quantum Leaps commercial licenses, which expressly supersede
* the GNU General Public License and are specifically designed for
* licensees interested in retaining the proprietary status of their code.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <www.gnu.org/licenses>.
*
* Contact information:
* <www.state-machine.com/licensing>
* <info@state-machine.com>
******************************************************************************
* @endcond
*/
#ifndef QS_PKG_H
#define QS_PKG_H

/****************************************************************************/
extern char_t const Q_BUILD_DATE[12];
extern char_t const Q_BUILD_TIME[9];

/****************************************************************************/
/*! Internal QS macro to insert an un-escaped byte into the QS buffer */
#define QS_INSERT_BYTE_(b_)       \
    QS_PTR_AT_(buf, head) = (b_); \
    ++head;                       \
    if (head == end) {            \
        head = (QSCtr)0;          \
    }

/****************************************************************************/
/*! Internal QS macro to insert an escaped byte into the QS buffer */
#define QS_INSERT_ESC_BYTE_(b_)                      \
    chksum = (uint8_t)(chksum + (b_));               \
    if (((b_) != QS_FRAME) && ((b_) != QS_ESC)) {    \
        QS_INSERT_BYTE_(b_)                          \
    }                                                \
    else {                                           \
        QS_INSERT_BYTE_(QS_ESC)                      \
        QS_INSERT_BYTE_((uint8_t)((b_) ^ QS_ESC_XOR))\
        ++QS_priv_.used;                             \
    }

/****************************************************************************/
/*! Internal QS macro to increment the given pointer parameter @p ptr_ */
/**
* @note Incrementing a pointer violates the MISRA-C 2004 Rule 17.4(req),
* pointer arithmetic other than array indexing. Encapsulating this violation
* in a macro allows to selectively suppress this specific deviation.
*/
#define QS_PTR_INC_(ptr_) (++(ptr_))

/****************************************************************************/
/*! Frame character of the QS output protocol */
#define QS_FRAME    ((uint8_t)0x7E)

/****************************************************************************/
/*! Escape character of the QS output protocol */
#define QS_ESC      ((uint8_t)0x7D)

/****************************************************************************/
/*! The expected checksum value over an uncorrupted QS record */
#define QS_GOOD_CHKSUM ((uint8_t)0xFF)

/****************************************************************************/
/*! Escape modifier of the QS output protocol */
/**
* @description
* The escaped byte is XOR-ed with the escape modifier before it is inserted
* into the QS buffer.
*/
#define QS_ESC_XOR  ((uint8_t)0x20)

/****************************************************************************/
/*! send the predefined target info trace record
 * (object sizes, build time-stamp, QP version) */
void QS_target_info_pre_(uint8_t isReset);

#endif  /* QS_PKG_H */

