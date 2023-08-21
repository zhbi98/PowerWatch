/**
 * @file nt_account.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "nt_account.h"

/**********************
 *  STATIC PROTOTYPES
 **********************/
static nt_acct_t * nt_acct_find_from_group(lv_ll_t * acct_group_p, 
    const int8_t * acct_id);
static int32_t notify(nt_acct_t * acct_p, nt_acct_t * pub_p,
    const void * data_p, uint32_t size);
static int32_t pull(nt_acct_t * acct_p, nt_acct_t * pub_p, 
    void * data_p, uint32_t size);
/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Construct an account for the associated communication model so that the other 
 * account communication model can publish data to that account for acceptance.
 * @param acct_p pointer to an initialized 'nt_acct_t' variable. Only its pointer is saved!
 * @param acct_id account name.
 * @param bufsize account name.
 * @param userdata
 * @return constructor result.
 */
uint8_t nt_acct_constructor(nt_acct_t * acct_p, const int8_t * acct_id, 
    uint32_t bufsize, void * userdata)
{
    memset(&acct_p->priv, 0, sizeof(struct _nt_priv_t));

    acct_p->acct_id = acct_id;
    acct_p->priv.buffersize = bufsize;
    acct_p->userdata = userdata;

    if (bufsize != 0) {
        uint8_t * buf0 = lv_mem_alloc(sizeof(uint8_t) * bufsize);
        if (!buf0) return NT_ACCT_INV;
        uint8_t * buf1 = lv_mem_alloc(sizeof(uint8_t) * bufsize);
        if (!buf1) {
            lv_mem_free(buf0);
            return NT_ACCT_INV;
        }

        lv_memset_00(buf0, bufsize);
        lv_memset_00(buf1, bufsize);

        nt_ppbuf_init(&acct_p->priv.ppbuf, buf0, buf1);

        acct_p->priv.buf0 = buf0;
        acct_p->priv.buf1 = buf1;
    }

    _lv_ll_init(&acct_p->publishers_ll, sizeof(nt_acct_t));
    _lv_ll_init(&acct_p->subscribers_ll, sizeof(nt_acct_t));
    return NT_ACCT_OK;
}

/**
 * Destroy accounts that are no longer in use, and release the cache that 
 * stores the list of concerns and the list of concerns.
 * @param acct_p pointer to an 'nt_acct_t' variable. Only its pointer is saved!
 */
void nt_acct_destructor(nt_acct_t * acct_p)
{
    nt_acct_t * _acct;

    while(acct_p->publishers_ll.head) {
        _acct = _lv_ll_get_head(&acct_p->publishers_ll);
        _lv_ll_remove(&acct_p->publishers_ll, _acct);
        lv_mem_free(_acct);
    }
    _lv_ll_clear(&acct_p->publishers_ll);

    while(acct_p->subscribers_ll.head) {
        _acct = _lv_ll_get_head(&acct_p->subscribers_ll);
        _lv_ll_remove(&acct_p->subscribers_ll, _acct);
        lv_mem_free(_acct);
    }
    _lv_ll_clear(&acct_p->subscribers_ll);

    lv_mem_free(acct_p->priv.buf0);
    lv_mem_free(acct_p->priv.buf1);
}

/**
 * Use this account to follow a publisher.
 * @param acct_p pointer to an 'nt_acct_t' variable point to follow a publisher
 * the account of the content publisher you are interested in
 * @param pub_id specifies the user name of the content publisher.
 * @return pointer to find the account.
 */
static nt_acct_t * nt_acct_find_from_group(lv_ll_t * acct_group_p, 
    const int8_t * acct_id)
{
    nt_acct_t * _acct_p;

    _LV_LL_READ_BACK(acct_group_p, _acct_p) {
        if (!strcmp(acct_id, _acct_p->acct_id))
            return _acct_p;
    }
    return NULL;
}

/**
 * Use this account to follow a publisher.
 * @param acct_p pointer to an 'nt_acct_t' variable point to 
 * focus on the account of the publisher's account id.
 * @param pub_id Specifies the user name of the publisher of the content to follow.
 * @return pointer to find the account.
 */
nt_acct_t * nt_acct_subscribe(nt_acct_t * acct_p, const int8_t * pub_id)
{
    /*Not allowed to subscribe to yourself*/
    if (strcmp(pub_id, acct_p->acct_id) == 0) return NULL;

    /*Multiple subscriptions to the same content publisher*/
    nt_acct_t * acct_pub = nt_acct_find_from_group(
        &acct_p->publishers_ll, pub_id);
    if (acct_pub != NULL)
        return NULL;

    /*Add the publisher to the subscription list*/
    nt_acct_t * publishers = _lv_ll_ins_head(&acct_p->publishers_ll);
    LV_ASSERT_MALLOC(publishers);
    memcpy(publishers, acct_pub, sizeof(nt_acct_t));

    /*Let the publisher add this subscriber*/
    nt_acct_t * subscribers = _lv_ll_ins_head(&acct_pub->subscribers_ll);
    LV_ASSERT_MALLOC(subscribers);
    memcpy(subscribers, acct_p, sizeof(nt_acct_t));
}

/**
 * Use this account to follow a publisher.
 * @param acct_p pointer to an 'nt_acct_t' variable point to 
 * focus on the account of the publisher's account id.
 * @param pub_id the name of the account associated with the publisher 
 * of the content that the current account has followed.
 * @return pointer to find the account.
 */
uint8_t nt_acct_unsubscribe(nt_acct_t * acct_p, const int8_t * pub_id)
{
    /*Multiple subscriptions to the same content publisher*/
    nt_acct_t * acct_pub = nt_acct_find_from_group(
        &acct_p->publishers_ll, pub_id);
    if (acct_pub == NULL)
        return NT_ACCT_INV;

    /*Remove the publisher from the subscription list*/
    _lv_ll_remove(&acct_p->publishers_ll, acct_pub);
    lv_mem_free(acct_pub);
    /*Let the publisher add this subscriber*/
    _lv_ll_remove(&acct_pub->subscribers_ll, acct_p);
    lv_mem_free(acct_p);
}

/**
 * Assign an account to submit content data for publication to his data area.
 * @param acct_p pointer to an 'nt_acct_t' variable The account to publish the content.
 * @param data_p content data to be published.
 * @return commit result.
 */
uint8_t nt_acct_commit(nt_acct_t * acct_p, const void * data_p, uint32_t size)
{
    if (!size || size != acct_p->priv.buffersize) return NT_ACCT_INV;

    void * wbuf;
    nt_ppbuf_get_write_buf(&acct_p->priv.ppbuf, &wbuf);

    memcpy(wbuf, data_p, size);

    nt_ppbuf_write_done(&acct_p->priv.ppbuf);

    return NT_ACCT_OK;
}

/**
 * Assign an account to submit content data for publication to his data area.
 * @param acct_p pointer to an 'nt_acct_t' variable The account to publish the content.
 * @param data_p content data to be published.
 * @return commit result.
 */
int32_t nt_acct_publish(nt_acct_t * acct_p)
{
    int32_t retval = NT_ACCT_RES_UNKNOW;
    void * rbuf = NULL;

    if (acct_p->priv.buffersize == 0)
        return NT_ACCT_RES_NO_CACHE;

    if (!nt_ppbuf_get_read_buf(&acct_p->priv.ppbuf, &rbuf))
        return NT_ACCT_RES_NO_COMMITED;

    _nt_acct_event_param_t param;
    param.event = NT_ACCT_EVENT_PUB_PUBLISH;
    param.tran = acct_p;
    param.recv = NULL;
    param.data_p = rbuf;
    param.size = acct_p->priv.buffersize;

    /*Publish messages to subscribers*/
    nt_acct_t * subscribers;

    _LV_LL_READ_BACK(&acct_p->subscribers_ll, subscribers) {
        int32_t (* callback)(struct _nt_acct_t * acct, 
            _nt_acct_event_param_t * param
        ) = subscribers->priv.event_callback;

        if (callback != NULL) {
            param.recv = subscribers;
            retval = callback(subscribers, &param);
        }
        else {
            continue;
        }
    }
    nt_ppbuf_read_done(&acct_p->priv.ppbuf);

    return retval;
}

/**
 * Followers actively pull data from content publisher accounts.
 * @param acct_p point to the current account.
 * @param pub_id the name of the account associated with the publisher 
 * of the content that the current account has followed.
 * @param data_p stores the content or data contained in the notification.
 * @param size the size, in bytes, of the data or content contained in the notification.
 * @return the result of the operation.
 */
int32_t nt_acct_pull_data(nt_acct_t * acct_p, const int8_t * pub_id, void * data_p, uint32_t size)
{
    /*Multiple subscriptions to the same content publisher*/
    nt_acct_t * acct_pub = nt_acct_find_from_group(
        &acct_p->publishers_ll, pub_id);
    if (acct_pub == NULL) return NT_ACCT_RES_NOT_FOUND;

    return pull(acct_p, acct_pub, data_p, size);
}

/**
 * Followers actively pull data from content publisher accounts.
 * @param acct_p pointer to an 'nt_acct_t' variable.
 * @param pub_p point to the account that published the information.
 * @param data_p stores the content or data contained in the notification.
 * @param size the size, in bytes, of the data or content contained in the notification.
 * @return the result of the operation.
 */
static int32_t pull(nt_acct_t * acct_p, nt_acct_t * pub_p, void * data_p, uint32_t size)
{
    int32_t retval = NT_ACCT_RES_UNKNOW;
    void * rbuf = NULL;
    if (pub_p == NULL) return NT_ACCT_RES_NOT_FOUND;

    int32_t (* callback)(struct _nt_acct_t * acct, 
        _nt_acct_event_param_t * param
    ) = pub_p->priv.event_callback;

    if (callback != NULL) {
        _nt_acct_event_param_t param; /*Construct the notification parameter*/
        param.event = NT_ACCT_EVENT_NOTIFY;
        param.tran = acct_p;
        param.recv = pub_p;
        param.data_p = (void *)data_p;
        param.size = size;

        int32_t ret = callback(pub_p, &param);
        retval = ret;
    }
    else {
        if (pub_p->priv.buffersize == size) {
            if (!nt_ppbuf_get_read_buf(&pub_p->priv.ppbuf, &rbuf)) {
                memcpy(data_p, rbuf, size);
                nt_ppbuf_read_done(&pub_p->priv.ppbuf);
                retval = 0;
            }
        }
        else {

        }
    }

    return retval;
}

/**
 * Send a notification to the account's followers, which can contain the notification content or data, 
 * or perform some action.
 * @param acct_p pointer to an 'nt_acct_t' variable.
 * @param pub_id the name of the account associated with the publisher 
 * of the content that the current account has followed
 * @param data_p stores the content or data contained in the notification.
 * @param size the size, in bytes, of the data or content contained in the notification.
 * @return the result of the operation.
 */
int32_t nt_acct_notify(nt_acct_t * acct_p, const int8_t * pub_id, const void * data_p, uint32_t size)
{
    /*Multiple subscriptions to the same content publisher*/
    nt_acct_t * acct_pub = nt_acct_find_from_group(
        &acct_p->publishers_ll, pub_id);

    if (acct_pub == NULL) return NT_ACCT_RES_NOT_FOUND;
    return notify(acct_p, acct_pub, data_p, size);
}

/**
 * Send a notification to the account's followers, which can contain the notification content or data, 
 * or perform some action.
 * @param acct_p pointer to an 'nt_acct_t' variable.
 * @param pub_p point to the account that published the information.
 * @param data_p stores the content or data contained in the notification.
 * @param size the size, in bytes, of the data or content contained in the notification.
 * @return the result of the operation.
 */
static int32_t notify(nt_acct_t * acct_p, nt_acct_t * pub_p, const void * data_p, uint32_t size)
{
    int32_t retval = NT_ACCT_RES_UNKNOW;
    if (pub_p == NULL) return NT_ACCT_RES_NOT_FOUND;

    int32_t (* callback)(struct _nt_acct_t * acct, 
        _nt_acct_event_param_t * param
    ) = pub_p->priv.event_callback;

    if (callback != NULL) {
        _nt_acct_event_param_t param; /*Construct the notification parameter*/
        param.event = NT_ACCT_EVENT_NOTIFY;
        param.tran = acct_p;
        param.recv = pub_p;
        param.data_p = (void *)data_p;
        param.size = size;

        int32_t ret = callback(pub_p, &param);
        retval = ret;
    }
    else {
        retval = NT_ACCT_RES_NO_CALLBACK;
    }

    return retval;
}

/**
 * Sets the event callback function for the specified account.
 * @param acct_p pointer to an 'nt_acct_t' variable need set callback account.
 * @param callback the callback function to which to connect.
 */
void nt_acct_set_event_callback(nt_acct_t * acct_p, int32_t (* callback)(
    struct _nt_acct_t * acct, _nt_acct_event_param_t * param))
{
    acct_p->priv.event_callback = callback;
}

/**
 * A callback function is distributed with timed content, and the corresponding 
 * callback function is called based on the account.
 * @param timer pointer to an 'lv_timer_t' variable A timer that performs a timed callback.
 */
void nt_acct_timer_callback_handler(lv_timer_t * timer)
{
    nt_acct_t * instance = (nt_acct_t *)(timer->user_data);

    int32_t (* callback)(struct _nt_acct_t * acct, 
        _nt_acct_event_param_t * param
    ) = instance->priv.event_callback;

    if (callback != NULL) {
        _nt_acct_event_param_t param;
        param.event = NT_ACCT_EVENT_TIMER;
        param.tran = instance;
        param.recv = instance;
        param.data_p = NULL;
        param.size = 0;

        callback(instance, &param);
    }
}

/**
 * Sets the firing period of the timer for the timed task.
 * @param acct_p pointer to an 'nt_acct_t' variable the account to set up for the timing cycle.
 * @param period period of the timer.
 */
void nt_acct_set_timer_period(nt_acct_t * acct_p, uint32_t period)
{
    if (acct_p->priv.timer) {
        lv_timer_del(acct_p->priv.timer);
        acct_p->priv.timer = NULL;
    }

    if (!period) return;

    acct_p->priv.timer = lv_timer_create(
        nt_acct_timer_callback_handler,
        period,
        acct_p
    );
}

/**
 * Start or stop the timer.
 * @param acct_p pointer to an 'nt_acct_t' variable of need start or stop timer account.
 * @param en start or stop.
 */
void nt_acct_set_timer_enable(nt_acct_t * acct_p, bool en)
{
    lv_timer_t * timer = acct_p->priv.timer;
    if (timer == NULL) return;
    (en) ? lv_timer_resume(timer) : lv_timer_pause(timer);
}

/**
 * Gets the number of content publishers followed by the current account.
 * @param acct_p Point to the account that is currently being viewed.
 * @return the number of followers.
 */
uint32_t nt_acct_get_publishers_size(nt_acct_t * acct_p)
{
    return _lv_ll_get_len(&acct_p->publishers_ll);
}

/**
 * Get the number of followers for the current account.
 * @param acct_p Point to the account that is currently being viewed.
 * @return the number of people who are followed.
 */
uint32_t nt_acct_get_subscribers_size(nt_acct_t * acct_p)
{
    return _lv_ll_get_len(&acct_p->subscribers_ll);
}
