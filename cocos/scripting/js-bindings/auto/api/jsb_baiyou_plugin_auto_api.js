/**
 * @module baiyou_plugin
 */
var baiyou = baiyou || {};

/**
 * @class BaiyouPlugin
 */
baiyou.BaiyouPlugin = {

/**
 * @method getBundleVersion
 * @return {String}
 */
getBundleVersion : function (
)
{
    return ;
},

/**
 * @method MessageBox
 * @param {String} arg0
 * @param {String} arg1
 */
MessageBox : function (
str, 
str 
)
{
},

/**
 * @method openURL
 * @param {String} arg0
 */
openURL : function (
str 
)
{
},

/**
 * @method unScheduleAllLocalNotification
 */
unScheduleAllLocalNotification : function (
)
{
},

/**
 * @method scheduleLocalNotification
 * @param {String} arg0
 * @param {String} arg1
 * @param {int} arg2
 */
scheduleLocalNotification : function (
str, 
str, 
int 
)
{
},

/**
 * @method getBundleId
 * @return {String}
 */
getBundleId : function (
)
{
    return ;
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method setIdleTimerDisabled
 * @param {bool} arg0
 */
setIdleTimerDisabled : function (
bool 
)
{
},

/**
 * @method getProperty
 * @param {String} arg0
 * @return {String}
 */
getProperty : function (
str 
)
{
    return ;
},

/**
 * @method getUUID
 * @return {String}
 */
getUUID : function (
)
{
    return ;
},

/**
 * @method restart
 */
restart : function (
)
{
},

/**
 * @method getDeviceInfo
 * @return {String}
 */
getDeviceInfo : function (
)
{
    return ;
},

/**
 * @method GetAnySDKUserInitFinished
 * @return {bool}
 */
GetAnySDKUserInitFinished : function (
)
{
    return false;
},

/**
 * @method SetAnySDKUserInitFinished
 * @param {bool} arg0
 */
SetAnySDKUserInitFinished : function (
bool 
)
{
},

/**
 * @method getInstance
 * @return {baiyou::BaiyouPlugin}
 */
getInstance : function (
)
{
    return baiyou::BaiyouPlugin;
},

};

/**
 * @class SDKUserInfo
 */
baiyou.SDKUserInfo = {

/**
 * @method setUserName
 * @param {String} arg0
 */
setUserName : function (
str 
)
{
},

/**
 * @method getUserId
 * @return {String}
 */
getUserId : function (
)
{
    return ;
},

/**
 * @method getAlias
 * @return {String}
 */
getAlias : function (
)
{
    return ;
},

/**
 * @method setUserId
 * @param {String} arg0
 */
setUserId : function (
str 
)
{
},

/**
 * @method setAlias
 * @param {String} arg0
 */
setAlias : function (
str 
)
{
},

/**
 * @method getUserName
 * @return {String}
 */
getUserName : function (
)
{
    return ;
},

};

/**
 * @class SDKCenter
 */
baiyou.SDKCenter = {

/**
 * @method getUserInfo
 * @param {int} arg0
 * @return {baiyou::SDKUserInfo}
 */
getUserInfo : function (
int 
)
{
    return baiyou::SDKUserInfo;
},

/**
 * @method Pay
 * @param {int} arg0
 */
Pay : function (
int 
)
{
},

/**
 * @method init
 * @param {Array} arg0
 * @return {bool}
 */
init : function (
array 
)
{
    return false;
},

/**
 * @method Logout
 * @param {int} arg0
 */
Logout : function (
int 
)
{
},

/**
 * @method Login
 * @param {int} arg0
 */
Login : function (
int 
)
{
},

/**
 * @method getInstance
 * @return {baiyou::SDKCenter}
 */
getInstance : function (
)
{
    return baiyou::SDKCenter;
},

/**
 * @method SDKCenter
 * @constructor
 */
SDKCenter : function (
)
{
},

};
