/**
 * @file nt_master.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "nt_master.h"

/**********************
 *  STATIC PROTOTYPES
 **********************/

static nt_acct_t * nt_master_find_from_list(lv_ll_t * acct_list, 
    const int8_t * acct_id);

/**********************
 * GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize NT master and initialize accounts list.
 * @param master_p pointer to an 'nt_master_t' variable is an account manager.
 */
void _nt_master_init(nt_master_t * master_p)
{
    _lv_ll_init(&master_p->accounts_ll, 
        sizeof(nt_acct_t *));
}

/**
 * Given the account name, look for information about the 
 * related account in the master account table.
 * @param acct_list pointer to an 'lv_ll_t' variable it's master account list.
 * @param acct_id the name of the account to find.
 * @return pointer to the account.
 */
static nt_acct_t * nt_master_find_from_list(
    lv_ll_t * acct_list, const int8_t * acct_id)
{
    nt_acct_t ** _node_p = NULL;
    nt_acct_t * _acct_p = NULL;

    _LV_LL_READ_BACK(acct_list, _node_p) {

        _acct_p = *_node_p;

        if (!strcmp(acct_id, _acct_p->acct_id))
            return _acct_p;
    }
    return NULL;
}

/**
 * Given the account name, look for information about the 
 * related account in the master account table.
 * @param acct_list pointer to an 'lv_ll_t' variable it's master account list.
 * @param acct_id the name of the account to find.
 * @return pointer to the account.
 */
static nt_acct_t ** nt_master_find_node_from_list(
    lv_ll_t * acct_list, const int8_t * acct_id)
{
    nt_acct_t ** _node_p = NULL;
    nt_acct_t * _acct_p = NULL;

    _LV_LL_READ_BACK(acct_list, _node_p) {

        _acct_p = *_node_p;

        if (!strcmp(acct_id, _acct_p->acct_id))
            return _node_p;
    }
    return NULL;
}

/**
 * Look for an account in the account management center.
 * @param master_p pointer to an 'nt_master_t' variable.
 * @param acct_id the name of the account to find.
 * @return pointer to find the account.
 */
nt_acct_t * nt_master_find_account(
    nt_master_t * master_p, const int8_t * acct_id)
{
    return nt_master_find_from_list(
        &master_p->accounts_ll, acct_id);
}

/**
 * Look for an account in the account management center.
 * @param master_p pointer to an 'nt_master_t' variable.
 * @param acct_id the name of the account to find.
 * @return pointer to find the account.
 */
nt_acct_t ** nt_master_find_node(
    nt_master_t * master_p, const int8_t * acct_id)
{
    return nt_master_find_node_from_list(
        &master_p->accounts_ll, acct_id);
}

/**
 * Add a new account to the account management center.
 * @param master_p pointer to an 'nt_master_t' variable.
 * @param acct_id the name of the account being added.
 * @return account add result.
 */
uint8_t nt_master_add_acct(nt_master_t * master_p, 
    nt_acct_t * acct_p)
{
    /*Account repeatedly added*/
    if (nt_master_find_account(master_p, 
        acct_p->acct_id) != NULL)
        return NT_MASTER_INV;

    /*Add the account to the account list*/
    nt_acct_t * account = _lv_ll_ins_head(
        &master_p->accounts_ll);
    LV_ASSERT_MALLOC(account);

    memcpy(account, &acct_p, sizeof(nt_acct_t *));
    return NT_MASTER_OK;
}

/**
 * Delete an account from the account management list.
 * @param master_p pointer to an 'nt_master_t' variable.
 * @param acct_p the name of the account being added.
 * @return account remove result.
 */
uint8_t nt_master_remove_acct(nt_master_t * master_p, 
    nt_acct_t * acct_p)
{
    nt_acct_t ** node_p = nt_master_find_node(
        master_p, acct_p->acct_id);

    /*Account was not found*/
    if (node_p != NULL) {
        /*Remove the account from the account list*/
        _lv_ll_remove(&master_p->accounts_ll, node_p);
        lv_mem_free(node_p);

        return NT_MASTER_OK;
    }
    return NT_MASTER_INV;
}

/**
 * Get the number of accounts contained in the account management center.
 * @param master_p pointer to an 'nt_master_t' variable.
 * @return number of account.
 */
uint32_t nt_master_get_len(nt_master_t * master_p)
{
    return _lv_ll_get_len(&master_p->accounts_ll);
}
