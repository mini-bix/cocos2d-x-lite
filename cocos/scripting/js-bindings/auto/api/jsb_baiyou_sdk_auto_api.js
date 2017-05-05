/**
 * @module baiyou_sdk
 */
var baiyou = baiyou || {};

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
 * @method getIsGuest
 * @return {bool}
 */
getIsGuest : function (
)
{
    return false;
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
 * @method setIsGuest
 * @param {bool} arg0
 */
setIsGuest : function (
bool 
)
{
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
 * @method OpenUserCenter
 * @param {int} arg0
 */
OpenUserCenter : function (
int 
)
{
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
 * @method handleURL
 * @param {char} arg0
 * @return {bool}
 */
handleURL : function (
char 
)
{
    return false;
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
 * @method openURL
 * @param {char} arg0
 * @return {bool}
 */
openURL : function (
char 
)
{
    return false;
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
