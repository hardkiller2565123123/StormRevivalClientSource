package script.xcmn_font
{
   import Struct.RubyInfo;
   import flash.display.BlendMode;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import flash.geom.Point;
   import flash.geom.Rectangle;
   import flash.text.TextField;
   import flash.text.TextFieldAutoSize;
   import flash.text.TextFormat;
   import flash.utils.Dictionary;
   
   public class FontParam extends MovieClip
   {
      
      public static const CCD_PIVOT_H_LEFT:uint = 1;
      
      public static const CCD_PIVOT_H_CENTER:uint = 2;
      
      public static const CCD_PIVOT_H_RIGHT:uint = 4;
      
      public static const CCD_PIVOT_V_TOP:uint = 8;
      
      public static const CCD_PIVOT_V_CENTER:uint = 16;
      
      public static const CCD_PIVOT_V_BOTTOM:uint = 32;
      
      public static const CCD_SHADOW_DISTANCE_X:Number = 4;
      
      public static const CCD_SHADOW_DISTANCE_Y:Number = 4;
      
      public static const CCD_TAG_TEXT_ICON:String = "<icon ";
      
      public static const CCD_TAG_TEXT_PLUS_1:String = "+";
      
      public static const CCD_TAG_TEXT_PLUS_2:String = "＋";
      
      public static const CCD_TAG_TEXT_STRING:String = "<string ";
      
      public static const CCD_TAG_TEXT_COLORING_S:String = "<color ";
      
      public static const CCD_TAG_TEXT_COLORING_E:String = "</color>";
      
      public static const CCD_TAG_TEXT_COLORING_RED:String = "red>";
      
      public static const CCD_TAG_TEXT_COLORING_BLUE:String = "blue>";
      
      public static const CCD_TAG_TEXT_COLORING_RED_L:String = "l_red>";
      
      public static const CCD_TAG_TEXT_RUBY_S:String = "<ruby ";
      
      public static const CCD_TAG_TEXT_RUBY_E:String = "</ruby>";
      
      public static const CCD_ICON_REPLACE_X_MARGIN:Number = 0;
      
      public static const CCD_ICON_REPLACE_Y_MARGIN:Number = 9;
      
      public static const CCD_BTN_ICON_REPLACE_Y_MARGIN_UP:Number = -10;
      
      public static const CCD_BTN_ICON_REPLACE_Y_MARGIN_DOWN:Number = 2;
      
      public static const CCD_ICON_MASK_X_MARGIN:Number = 0;
      
      public static const CCD_ICON_MASK_Y_MARGIN:Number = -3;
      
      public static const CCD_ICON_KEY_CODE_WIDTH:Number = 86;
      
      public static const CCD_ICON_KEY_CODE_WIDTH_WIDE:Number = 96;
      
      public static const CCD_ICON_MASK_HEIGHT_MARGIN:Number = 12;
      
      protected static const CCD_KEY_CODE:int = 0;
      
      protected static const CCD_KEY_CODE_WIDE:int = 1;
      
      protected static const CCD_USE_INDEX:String = "useIndex";
      
      protected static const CCD_USE_KEY_CODE_TYPE:String = "useKeyCode";
      
      public static const CCD_RUBI_GAP:int = 0;
      
      private static const CCD_TATWEEL_CODE:Number = 1600;
      
      private static const CCD_LIGATURE_SECOND_CODE:Number = 1604;
      
      private static const CCD_ACCENTED_LIGATURE_SECOND_CODE:Number = 1617;
      
      private static const m_ligatureFirstCode_Tbl:Array = new Array();
      
      private static const m_ligatureCode_Tbl:Array = new Array();
      
      private static const m_accentedLigatureFirstCode_Tbl:Array = new Array();
      
      private static const m_accentedLigatureCode_Tbl:Array = new Array();
      
      private static const CCD_SEPARATE_CODE:Number = 1569;
      
      private static const CCD_CHANGE_LAST_CODE:uint = 1;
      
      private static const CCD_CHANGE_FIRST_CODE:uint = 2;
      
      private static const CCD_CHANGE_CENTER_CODE:uint = 3;
      
      private static const CCD_ACCENTED_MIN_CODE:Number = 1611;
      
      private static const CCD_ACCENTED_MAX_CODE:Number = 1618;
      
      private static const CCD_ACCENTED_LIGATURE_MIN_CODE:Number = 64606;
      
      private static const CCD_ACCENTED_LIGATURE_MAX_CODE:Number = 64610;
      
      public static const CCD_TAG_LTR_MARK:String = "<mark LTR />";
      
      public static const CCD_TAG_RTL_MARK:String = "<mark RTL />";
      
      protected var m_btnIconMap:Dictionary = new Dictionary();
      
      private var m_actBtnIconMap:Array = new Array();
      
      private var m_actIconArr:Array = new Array();
      
      protected var m_playerSide:int = 0;
      
      private var m_wideIconKeyCode:Array = new Array();
      
      private var m_ArabicFormB_Tbl:Dictionary = null;
      
      private var m_2TypesFormB_Tbl:Dictionary = null;
      
      protected var m_isEngOnly:Boolean = false;
      
      public function FontParam()
      {
         super();
         this.m_playerSide = int(ExternalInterface.call("GetPad_1P"));
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_1 />"] = "btn_1";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_1_hld />"] = "btn_1_hld";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_2 />"] = "btn_2";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_2_hld />"] = "btn_2_hld";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_3 />"] = "btn_3";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_3_hld />"] = "btn_3_hld";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_4 />"] = "btn_4";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_4_hld />"] = "btn_4_hld";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_r1 />"] = "btn_r1";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_r1_hld />"] = "btn_r1_hld";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_l1 />"] = "btn_l1";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_l1_hld />"] = "btn_l1_hld";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_r2 />"] = "btn_r2";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_r2_hld />"] = "btn_r2_hld";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_l2 />"] = "btn_l2";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_l2_hld />"] = "btn_l2_hld";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "key />"] = "key";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "key_up />"] = "key_up";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "key_r />"] = "key_r";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "key_dwn />"] = "key_dwn";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "key_l />"] = "key_l";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stk_r />"] = "stk_r";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stk_r_roll />"] = "stk_r_roll";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stk_r_r />"] = "stk_r_r";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stk_r_l />"] = "stk_r_l";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stk_r_up />"] = "stk_r_up";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stk_r_dwn />"] = "stk_r_dwn";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stk_r3 />"] = "stk_r3";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stk_l />"] = "stk_l";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stk_l_roll />"] = "stk_l_roll";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stk_l_r />"] = "stk_l_r";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stk_l_l />"] = "stk_l_l";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stk_l_up />"] = "stk_l_up";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stk_l_dwn />"] = "stk_l_dwn";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_option />"] = "btn_select";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_share />"] = "btn_share";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "icon_plus />"] = "icon_plus";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "pad_touch />"] = "btn_start";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_lr />"] = "stk_l_r";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_ll />"] = "stk_l_l";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_ld />"] = "stk_l_dwn";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_lu />"] = "stk_l_up";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_rl />"] = "btn_3";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stick_l />"] = "stk_l";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stick_lu />"] = "stk_l_up";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stick_lr />"] = "stk_l_r";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stick_ld />"] = "stk_l_dwn";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stick_ll />"] = "stk_l_l";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stick_r />"] = "stk_r";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stick_ru />"] = "stk_r_up";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stick_rr />"] = "stk_r_r";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stick_rd />"] = "stk_r_dwn";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "stick_rl />"] = "stk_r_l";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "start />"] = "btn_start";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "select />"] = "btn_select";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_attack />"] = "btn_1";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_jump />"] = "btn_2";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_chakra />"] = "btn_4";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_shuriken />"] = "btn_3";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_supportl />"] = "btn_l1";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_supportr />"] = "btn_r1";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_kawarimi />"] = "btn_l2";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_guard />"] = "btn_r2";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "save />"] = "txt_icon_save";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "star />"] = "txt6";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "moji_music />"] = "txt1";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "moji_tm />"] = "txt2";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "moji_r />"] = "txt3";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "moji_infinity />"] = "txt4";
         this.m_btnIconMap[CCD_TAG_TEXT_ICON + "moji_bullet />"] = "txt5";
         this.m_actIconArr.push(CCD_TAG_TEXT_ICON + "btn_attack />");
         this.m_actIconArr.push(CCD_TAG_TEXT_ICON + "btn_jump />");
         this.m_actIconArr.push(CCD_TAG_TEXT_ICON + "btn_chakra />");
         this.m_actIconArr.push(CCD_TAG_TEXT_ICON + "btn_shuriken />");
         this.m_actIconArr.push(CCD_TAG_TEXT_ICON + "btn_supportl />");
         this.m_actIconArr.push(CCD_TAG_TEXT_ICON + "btn_supportr />");
         this.m_actIconArr.push(CCD_TAG_TEXT_ICON + "btn_kawarimi />");
         this.m_actIconArr.push(CCD_TAG_TEXT_ICON + "btn_guard />");
         this.ResetActionIconTag();
         this.SetPlayerActIconTag();
         var _loc1_:Array = new Array(ExternalInterface.call("GetRegionDependIconTagCode"));
         if(_loc1_[0] != null)
         {
            this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_ok />"] = _loc1_[0];
            this.m_btnIconMap[CCD_TAG_TEXT_ICON + "btn_cancel />"] = _loc1_[1];
         }
         else
         {
            ExternalInterface.call("CallAssertFromSwf","xcmn_font::FontParam.ResetAcionIconTag[ Undefined GetRegionDependIconTagCode ]");
         }
         this.m_wideIconKeyCode.push("stk");
         this.m_wideIconKeyCode.push("option");
         this.m_wideIconKeyCode.push("share");
         this.m_wideIconKeyCode.push("pad");
      }
      
      public function ResetActionIconTag() : *
      {
         var _loc1_:int = int(ExternalInterface.call("GetPad_1P"));
         var _loc2_:Array = ExternalInterface.call("GetBattleIconTagCode",_loc1_) as Array;
         var _loc3_:int = 0;
         if(_loc2_ != null)
         {
            while(_loc3_ < _loc2_.length)
            {
               trace("1P_Icon[" + _loc3_ + "]:" + _loc2_[_loc3_]);
               _loc3_++;
            }
            this.m_actBtnIconMap[_loc1_] = new Dictionary();
            this.m_actBtnIconMap[_loc1_][CCD_TAG_TEXT_ICON + "btn_attack />"] = _loc2_[0];
            this.m_actBtnIconMap[_loc1_][CCD_TAG_TEXT_ICON + "btn_jump />"] = _loc2_[1];
            this.m_actBtnIconMap[_loc1_][CCD_TAG_TEXT_ICON + "btn_chakra />"] = _loc2_[2];
            this.m_actBtnIconMap[_loc1_][CCD_TAG_TEXT_ICON + "btn_shuriken />"] = _loc2_[3];
            this.m_actBtnIconMap[_loc1_][CCD_TAG_TEXT_ICON + "btn_supportl />"] = _loc2_[4];
            this.m_actBtnIconMap[_loc1_][CCD_TAG_TEXT_ICON + "btn_supportr />"] = _loc2_[5];
            this.m_actBtnIconMap[_loc1_][CCD_TAG_TEXT_ICON + "btn_kawarimi />"] = _loc2_[6];
            this.m_actBtnIconMap[_loc1_][CCD_TAG_TEXT_ICON + "btn_guard />"] = _loc2_[7];
         }
         else
         {
            ExternalInterface.call("CallAssertFromSwf","xcmn_font::FontParam.ResetAcionIconTag[ UndefinedGetBattleIconTagCode ]");
         }
         _loc1_ = int(ExternalInterface.call("GetPad_2P"));
         _loc2_ = null;
         _loc2_ = ExternalInterface.call("GetBattleIconTagCode",_loc1_) as Array;
         if(_loc2_ != null)
         {
            _loc3_ = 0;
            while(_loc3_ < _loc2_.length)
            {
               trace("2P_Icon[" + _loc3_ + "]:" + _loc2_[_loc3_]);
               _loc3_++;
            }
            this.m_actBtnIconMap[_loc1_] = new Dictionary();
            this.m_actBtnIconMap[_loc1_][CCD_TAG_TEXT_ICON + "btn_attack />"] = _loc2_[0];
            this.m_actBtnIconMap[_loc1_][CCD_TAG_TEXT_ICON + "btn_jump />"] = _loc2_[1];
            this.m_actBtnIconMap[_loc1_][CCD_TAG_TEXT_ICON + "btn_chakra />"] = _loc2_[2];
            this.m_actBtnIconMap[_loc1_][CCD_TAG_TEXT_ICON + "btn_shuriken />"] = _loc2_[3];
            this.m_actBtnIconMap[_loc1_][CCD_TAG_TEXT_ICON + "btn_supportl />"] = _loc2_[4];
            this.m_actBtnIconMap[_loc1_][CCD_TAG_TEXT_ICON + "btn_supportr />"] = _loc2_[5];
            this.m_actBtnIconMap[_loc1_][CCD_TAG_TEXT_ICON + "btn_kawarimi />"] = _loc2_[6];
            this.m_actBtnIconMap[_loc1_][CCD_TAG_TEXT_ICON + "btn_guard />"] = _loc2_[7];
         }
         else
         {
            ExternalInterface.call("CallAssertFromSwf","xcmn_font::FontParam.ResetAcionIconTag[ UndefinedGetBattleIconTagCode ]");
         }
      }
      
      public function SetPlayerActIconTag() : *
      {
         var _loc1_:int = 0;
         while(_loc1_ < this.m_actIconArr.length)
         {
            if(Boolean(this.m_actBtnIconMap[this.m_playerSide]) && Boolean(this.m_actBtnIconMap[this.m_playerSide][this.m_actIconArr[_loc1_]] != null) && this.m_actBtnIconMap[this.m_playerSide][this.m_actIconArr[_loc1_]] != undefined)
            {
               this.m_btnIconMap[this.m_actIconArr[_loc1_]] = this.m_actBtnIconMap[this.m_playerSide][this.m_actIconArr[_loc1_]];
            }
            _loc1_++;
         }
      }
      
      protected function GetUseKeyCodeIndex(param1:String, param2:Array, param3:Array) : Object
      {
         var _loc4_:int = param1.indexOf(param3[CCD_KEY_CODE],param2[CCD_KEY_CODE]);
         var _loc5_:int = param1.indexOf(param3[CCD_KEY_CODE_WIDE],param2[CCD_KEY_CODE_WIDE]);
         var _loc6_:int = -1;
         var _loc7_:int = -1;
         if(_loc4_ != -1 && _loc5_ != -1)
         {
            if(_loc4_ <= _loc5_)
            {
               _loc6_ = _loc4_;
               _loc7_ = CCD_KEY_CODE;
            }
            else
            {
               _loc6_ = _loc5_;
               _loc7_ = CCD_KEY_CODE_WIDE;
            }
         }
         else if(_loc4_ != -1)
         {
            _loc6_ = _loc4_;
            _loc7_ = CCD_KEY_CODE;
         }
         else if(_loc5_ != -1)
         {
            _loc6_ = _loc5_;
            _loc7_ = CCD_KEY_CODE_WIDE;
         }
         var _loc8_:Object = new Object();
         _loc8_[CCD_USE_INDEX] = _loc6_;
         _loc8_[CCD_USE_KEY_CODE_TYPE] = _loc7_;
         return _loc8_;
      }
      
      protected function GetKeyCodeType(param1:String) : int
      {
         var _loc2_:int = CCD_KEY_CODE;
         var _loc3_:int = 0;
         while(_loc3_ < this.m_wideIconKeyCode.length)
         {
            if(param1.indexOf(this.m_wideIconKeyCode[_loc3_]) != -1)
            {
               _loc2_ = CCD_KEY_CODE_WIDE;
               break;
            }
            _loc3_++;
         }
         return _loc2_;
      }
      
      public function CreateRubyInfo(param1:TextField, param2:Array) : *
      {
         var _loc4_:Boolean = false;
         var _loc5_:Point = null;
         var _loc6_:int = 0;
         var _loc7_:Number = NaN;
         var _loc8_:String = null;
         var _loc9_:int = 0;
         var _loc10_:* = undefined;
         var _loc11_:Number = NaN;
         var _loc12_:String = null;
         var _loc13_:RubyInfo = null;
         param2.length = 0;
         var _loc3_:int = -1;
         while(1)
         {
            _loc3_ = param1.text.indexOf(CCD_TAG_TEXT_RUBY_S,_loc3_);
            if(_loc3_ == -1)
            {
               break;
            }
            _loc4_ = false;
            _loc5_ = new Point();
            _loc6_ = param1.text.indexOf(">",_loc3_ + CCD_TAG_TEXT_RUBY_S.length);
            if(_loc6_ != -1)
            {
               _loc7_ = _loc6_ - (_loc3_ + CCD_TAG_TEXT_RUBY_S.length);
               _loc8_ = param1.text.substr(_loc3_ + CCD_TAG_TEXT_RUBY_S.length,_loc7_);
               _loc9_ = param1.text.indexOf(CCD_TAG_TEXT_RUBY_E,_loc3_ + CCD_TAG_TEXT_RUBY_S.length);
               if(_loc9_ != -1)
               {
                  _loc10_ = CCD_TAG_TEXT_RUBY_S.length + _loc7_ + 1;
                  _loc11_ = _loc9_ - (_loc3_ + _loc10_);
                  _loc12_ = param1.text.substr(_loc3_ + _loc10_,_loc11_);
                  param1.replaceText(_loc9_,_loc9_ + CCD_TAG_TEXT_RUBY_E.length,"");
                  param1.replaceText(_loc3_,_loc3_ + _loc10_,"");
                  _loc13_ = new RubyInfo(_loc12_,_loc8_);
                  param2.push(_loc13_);
                  _loc4_ = true;
               }
            }
            if(_loc4_ == false)
            {
               trace("ルビタグ検索の失敗");
               break;
            }
         }
      }
      
      public function InsertRuby(param1:MovieClip, param2:TextField, param3:TextFormat, param4:Array, param5:Array) : *
      {
         var _loc6_:int = 0;
         var _loc7_:int = 0;
         var _loc8_:Rectangle = null;
         var _loc9_:Rectangle = null;
         var _loc10_:Point = null;
         var _loc11_:TextField = null;
         var _loc12_:TextFormat = null;
         if(param5.length > 0)
         {
            _loc6_ = 0;
            while(_loc6_ < param5.length)
            {
               param1.removeChild(param5[_loc6_]);
               _loc6_++;
            }
            param5.length = 0;
         }
         _loc6_ = 0;
         while(_loc6_ < param4.length)
         {
            _loc7_ = -1;
            while(1)
            {
               _loc7_ = param2.text.indexOf(param4[_loc6_].m_keyStr,_loc7_);
               if(_loc7_ == -1)
               {
                  break;
               }
               _loc8_ = new Rectangle();
               _loc8_ = param2.getCharBoundaries(_loc7_ + param4[_loc6_].m_keyStr.length - 1);
               _loc9_ = new Rectangle();
               _loc9_ = param2.getCharBoundaries(_loc7_);
               _loc10_ = new Point();
               _loc10_.x = _loc9_.left + Math.abs(_loc8_.right - _loc9_.left) / 2;
               _loc10_.y = param2.y + _loc9_.top;
               _loc11_ = new TextField();
               _loc11_.autoSize = TextFieldAutoSize.LEFT;
               _loc11_.text = param4[_loc6_].m_ruby;
               _loc12_ = new TextFormat();
               _loc12_ = param3;
               _loc12_.color = uint(param2.getTextFormat(_loc7_,_loc7_ + 1).color);
               _loc11_.setTextFormat(_loc12_);
               _loc11_.x = _loc10_.x - _loc11_.width / 2;
               _loc11_.y = _loc10_.y - _loc11_.height / 1.5;
               param5.push(_loc11_);
               param1.addChild(_loc11_);
               _loc7_ += param4[_loc6_].m_keyStr.length;
            }
            _loc6_++;
         }
      }
      
      protected function InitializeArabicParam() : *
      {
         this.m_ArabicFormB_Tbl = null;
         this.m_ArabicFormB_Tbl = new Dictionary();
         this.m_ArabicFormB_Tbl[1605] = 65249;
         this.m_ArabicFormB_Tbl[1606] = 65253;
         this.m_ArabicFormB_Tbl[1607] = 65257;
         this.m_ArabicFormB_Tbl[1608] = 65261;
         this.m_ArabicFormB_Tbl[1609] = 65263;
         this.m_ArabicFormB_Tbl[1610] = 65265;
         this.m_ArabicFormB_Tbl[1569] = 65152;
         this.m_ArabicFormB_Tbl[1570] = 65153;
         this.m_ArabicFormB_Tbl[1571] = 65155;
         this.m_ArabicFormB_Tbl[1572] = 65157;
         this.m_ArabicFormB_Tbl[1573] = 65159;
         this.m_ArabicFormB_Tbl[1574] = 65161;
         this.m_ArabicFormB_Tbl[1575] = 65165;
         this.m_ArabicFormB_Tbl[1576] = 65167;
         this.m_ArabicFormB_Tbl[1577] = 65171;
         this.m_ArabicFormB_Tbl[1578] = 65173;
         this.m_ArabicFormB_Tbl[1579] = 65177;
         this.m_ArabicFormB_Tbl[1580] = 65181;
         this.m_ArabicFormB_Tbl[1581] = 65185;
         this.m_ArabicFormB_Tbl[1582] = 65189;
         this.m_ArabicFormB_Tbl[1583] = 65193;
         this.m_ArabicFormB_Tbl[1584] = 65195;
         this.m_ArabicFormB_Tbl[1585] = 65197;
         this.m_ArabicFormB_Tbl[1586] = 65199;
         this.m_ArabicFormB_Tbl[1587] = 65201;
         this.m_ArabicFormB_Tbl[1588] = 65205;
         this.m_ArabicFormB_Tbl[1589] = 65209;
         this.m_ArabicFormB_Tbl[1590] = 65213;
         this.m_ArabicFormB_Tbl[1591] = 65217;
         this.m_ArabicFormB_Tbl[1592] = 65221;
         this.m_ArabicFormB_Tbl[1593] = 65225;
         this.m_ArabicFormB_Tbl[1594] = 65229;
         this.m_ArabicFormB_Tbl[1601] = 65233;
         this.m_ArabicFormB_Tbl[1602] = 65237;
         this.m_ArabicFormB_Tbl[1603] = 65241;
         this.m_ArabicFormB_Tbl[1604] = 65245;
         this.m_2TypesFormB_Tbl = null;
         this.m_2TypesFormB_Tbl = new Dictionary();
         this.m_2TypesFormB_Tbl[1608] = this.m_ArabicFormB_Tbl[1608];
         this.m_2TypesFormB_Tbl[1609] = this.m_ArabicFormB_Tbl[1609];
         this.m_2TypesFormB_Tbl[1570] = this.m_ArabicFormB_Tbl[1570];
         this.m_2TypesFormB_Tbl[1571] = this.m_ArabicFormB_Tbl[1571];
         this.m_2TypesFormB_Tbl[1572] = this.m_ArabicFormB_Tbl[1572];
         this.m_2TypesFormB_Tbl[1573] = this.m_ArabicFormB_Tbl[1573];
         this.m_2TypesFormB_Tbl[1575] = this.m_ArabicFormB_Tbl[1575];
         this.m_2TypesFormB_Tbl[1577] = this.m_ArabicFormB_Tbl[1577];
         this.m_2TypesFormB_Tbl[1583] = this.m_ArabicFormB_Tbl[1583];
         this.m_2TypesFormB_Tbl[1584] = this.m_ArabicFormB_Tbl[1584];
         this.m_2TypesFormB_Tbl[1585] = this.m_ArabicFormB_Tbl[1585];
         this.m_2TypesFormB_Tbl[1586] = this.m_ArabicFormB_Tbl[1586];
         m_ligatureFirstCode_Tbl.length = 0;
         m_ligatureFirstCode_Tbl.push(1570);
         m_ligatureFirstCode_Tbl.push(1571);
         m_ligatureFirstCode_Tbl.push(1573);
         m_ligatureFirstCode_Tbl.push(1575);
         m_ligatureCode_Tbl.length = 0;
         m_ligatureCode_Tbl.push(65269);
         m_ligatureCode_Tbl.push(65271);
         m_ligatureCode_Tbl.push(65273);
         m_ligatureCode_Tbl.push(65275);
         m_accentedLigatureFirstCode_Tbl.length = 0;
         m_accentedLigatureFirstCode_Tbl.push(1612);
         m_accentedLigatureFirstCode_Tbl.push(1613);
         m_accentedLigatureFirstCode_Tbl.push(1614);
         m_accentedLigatureFirstCode_Tbl.push(1615);
         m_accentedLigatureFirstCode_Tbl.push(1616);
         m_accentedLigatureCode_Tbl.length = 0;
         m_accentedLigatureCode_Tbl.push(64606);
         m_accentedLigatureCode_Tbl.push(64607);
         m_accentedLigatureCode_Tbl.push(64608);
         m_accentedLigatureCode_Tbl.push(64609);
         m_accentedLigatureCode_Tbl.push(64610);
      }
      
      public function ConvertArabic(param1:TextField) : *
      {
         this.CalcArabicTag(param1);
         this.CheckBracketsReverse(param1);
         this.CheckMirroringFont(param1);
         this.ConvertLigature(param1);
         this.ConvertPositionCode(param1);
      }
      
      private function ConvertLigature(param1:TextField) : *
      {
         var _loc3_:int = 0;
         if(m_ligatureFirstCode_Tbl.length == 1)
         {
            return;
         }
         var _loc2_:int = 0;
         while(1)
         {
            _loc2_ = param1.text.indexOf(String.fromCharCode(CCD_LIGATURE_SECOND_CODE),_loc2_);
            if(_loc2_ == -1)
            {
               break;
            }
            _loc3_ = 0;
            while(_loc3_ < m_ligatureFirstCode_Tbl.length)
            {
               if(param1.text.charCodeAt(_loc2_ + 1) == m_ligatureFirstCode_Tbl[_loc3_])
               {
                  param1.replaceText(_loc2_,_loc2_ + 2,String.fromCharCode(m_ligatureCode_Tbl[_loc3_]));
                  break;
               }
               _loc3_++;
            }
            _loc2_++;
         }
         _loc2_ = -1;
         while(1)
         {
            _loc2_ = param1.text.indexOf(String.fromCharCode(CCD_ACCENTED_LIGATURE_SECOND_CODE),_loc2_);
            if(_loc2_ == -1)
            {
               break;
            }
            _loc3_ = 0;
            while(_loc3_ < m_accentedLigatureFirstCode_Tbl.length)
            {
               if(param1.text.charCodeAt(_loc2_ + 1) == m_accentedLigatureFirstCode_Tbl[_loc3_])
               {
                  param1.replaceText(_loc2_,_loc2_ + 2,String.fromCharCode(m_accentedLigatureCode_Tbl[_loc3_]));
                  break;
               }
               _loc3_++;
            }
            _loc2_++;
         }
      }
      
      private function ConvertPositionCode(param1:TextField) : *
      {
         var _loc3_:uint = 0;
         var _loc4_:Number = NaN;
         var _loc5_:Boolean = false;
         var _loc6_:int = 0;
         var _loc7_:Boolean = false;
         var _loc8_:Boolean = false;
         if(param1.text.length == 1)
         {
            if(this.m_ArabicFormB_Tbl[param1.text.charCodeAt(0)] != undefined)
            {
               param1.replaceText(0,1,this.m_ArabicFormB_Tbl[param1.text.charCodeAt(0)]);
               return;
            }
         }
         var _loc2_:int = 0;
         while(_loc2_ < param1.text.length)
         {
            _loc3_ = 0;
            _loc4_ = param1.text.charCodeAt(_loc2_);
            _loc5_ = false;
            _loc6_ = 0;
            while(_loc6_ < m_ligatureCode_Tbl.length)
            {
               if(_loc4_ == m_ligatureCode_Tbl[_loc6_])
               {
                  _loc5_ = true;
                  break;
               }
               _loc6_++;
            }
            if(this.m_ArabicFormB_Tbl[_loc4_] != undefined || _loc5_ == true)
            {
               if(_loc4_ != CCD_SEPARATE_CODE)
               {
                  if(_loc2_ == 0)
                  {
                     if(this.m_2TypesFormB_Tbl[param1.text.charCodeAt(_loc2_)] == undefined && _loc5_ == false)
                     {
                        if(this.CheckBackFontCenterForm(param1.text,_loc2_) == true)
                        {
                           _loc3_ = CCD_CHANGE_FIRST_CODE;
                        }
                     }
                  }
                  else if(_loc2_ == param1.text.length - 1)
                  {
                     if(this.CheckFrontFontCenterForm(param1.text,_loc2_) == true)
                     {
                        _loc3_ = CCD_CHANGE_LAST_CODE;
                     }
                  }
                  else
                  {
                     _loc7_ = this.CheckFrontFontCenterForm(param1.text,_loc2_);
                     _loc8_ = this.CheckBackFontCenterForm(param1.text,_loc2_);
                     if(_loc7_ && _loc8_)
                     {
                        if(this.m_2TypesFormB_Tbl[_loc4_] == undefined)
                        {
                           if(_loc5_ == false)
                           {
                              _loc3_ = CCD_CHANGE_CENTER_CODE;
                           }
                           else
                           {
                              _loc3_ = CCD_CHANGE_LAST_CODE;
                           }
                        }
                        else
                        {
                           _loc3_ = CCD_CHANGE_LAST_CODE;
                        }
                     }
                     else if(_loc7_ == true)
                     {
                        _loc3_ = CCD_CHANGE_LAST_CODE;
                     }
                     else if(_loc8_ == true)
                     {
                        if(this.m_2TypesFormB_Tbl[_loc4_] == undefined && _loc5_ == false)
                        {
                           _loc3_ = CCD_CHANGE_FIRST_CODE;
                        }
                     }
                  }
                  if(_loc5_ == true)
                  {
                     param1.replaceText(_loc2_,_loc2_ + 1,String.fromCharCode(_loc4_ + _loc3_));
                  }
                  else
                  {
                     param1.replaceText(_loc2_,_loc2_ + 1,String.fromCharCode(this.m_ArabicFormB_Tbl[_loc4_] + _loc3_));
                  }
               }
            }
            _loc2_++;
         }
      }
      
      private function CheckFrontFontCenterForm(param1:String, param2:int) : Boolean
      {
         var _loc6_:* = undefined;
         var _loc7_:* = undefined;
         var _loc3_:* = -1;
         while(1)
         {
            if(param1.charCodeAt(param2 + _loc3_) >= CCD_ACCENTED_MIN_CODE && param1.charCodeAt(param2 + _loc3_) <= CCD_ACCENTED_MAX_CODE)
            {
               _loc3_--;
            }
            else
            {
               if(!(param1.charCodeAt(param2 + _loc3_) >= CCD_ACCENTED_LIGATURE_MIN_CODE && param1.charCodeAt(param2 + _loc3_) <= CCD_ACCENTED_LIGATURE_MAX_CODE))
               {
                  break;
               }
               _loc3_--;
            }
         }
         var _loc4_:Boolean = false;
         var _loc5_:Number = param1.charCodeAt(param2 + _loc3_);
         for(_loc6_ in this.m_2TypesFormB_Tbl)
         {
            if(_loc5_ == this.m_2TypesFormB_Tbl[_loc6_])
            {
               return _loc4_;
            }
            if(_loc5_ == this.m_2TypesFormB_Tbl[_loc6_] + CCD_CHANGE_LAST_CODE)
            {
               return _loc4_;
            }
         }
         if(_loc5_ != CCD_SEPARATE_CODE)
         {
            if(_loc5_ == CCD_TATWEEL_CODE)
            {
               _loc4_ = true;
            }
            else
            {
               for(_loc7_ in this.m_ArabicFormB_Tbl)
               {
                  if(_loc5_ == this.m_ArabicFormB_Tbl[_loc7_] + CCD_CHANGE_FIRST_CODE)
                  {
                     _loc4_ = true;
                     break;
                  }
                  if(_loc5_ == this.m_ArabicFormB_Tbl[_loc7_] + CCD_CHANGE_CENTER_CODE)
                  {
                     _loc4_ = true;
                     break;
                  }
               }
            }
         }
         return _loc4_;
      }
      
      private function CheckBackFontCenterForm(param1:String, param2:int) : Boolean
      {
         var _loc6_:int = 0;
         var _loc3_:int = 1;
         while(1)
         {
            if(param1.charCodeAt(param2 + _loc3_) >= CCD_ACCENTED_MIN_CODE && param1.charCodeAt(param2 + _loc3_) <= CCD_ACCENTED_MAX_CODE)
            {
               _loc3_++;
            }
            else
            {
               if(!(param1.charCodeAt(param2 + _loc3_) >= CCD_ACCENTED_LIGATURE_MIN_CODE && param1.charCodeAt(param2 + _loc3_) <= CCD_ACCENTED_LIGATURE_MAX_CODE))
               {
                  break;
               }
               _loc3_++;
            }
         }
         var _loc4_:Boolean = false;
         var _loc5_:Number = param1.charCodeAt(param2 + _loc3_);
         if(_loc5_ != CCD_SEPARATE_CODE)
         {
            if(_loc5_ == CCD_TATWEEL_CODE)
            {
               _loc4_ = true;
            }
            else if(this.m_ArabicFormB_Tbl[_loc5_] != undefined)
            {
               _loc4_ = true;
            }
            else
            {
               _loc6_ = 0;
               while(_loc6_ < m_ligatureCode_Tbl.length)
               {
                  if(_loc5_ == m_ligatureCode_Tbl[_loc6_])
                  {
                     _loc4_ = true;
                     break;
                  }
                  _loc6_++;
               }
            }
         }
         return _loc4_;
      }
      
      public function CheckMirroringFont(param1:TextField) : *
      {
         var _loc3_:Boolean = false;
         var _loc4_:Number = NaN;
         var _loc2_:Number = -1;
         while(1)
         {
            _loc2_ = param1.text.indexOf(".",_loc2_);
            if(_loc2_ == -1)
            {
               break;
            }
            _loc3_ = false;
            if(_loc2_ == param1.text.length - 1)
            {
               param1.replaceText(_loc2_,_loc2_ + 1,String.fromCharCode(8207) + ".");
               _loc2_ += 2;
            }
            else
            {
               _loc4_ = param1.text.charCodeAt(_loc2_ - 1);
               if(_loc4_ < 32 || _loc4_ > 127)
               {
                  param1.replaceText(_loc2_,_loc2_ + 1,String.fromCharCode(8207) + "." + String.fromCharCode(8207));
                  _loc2_ += 3;
               }
               else
               {
                  _loc2_++;
               }
            }
         }
         _loc2_ = -1;
         _loc2_ = param1.text.indexOf(":",_loc2_);
         if(_loc2_ != -1)
         {
            _loc4_ = param1.text.charCodeAt(_loc2_ - 1);
            if(_loc4_ < 32 || _loc4_ > 127)
            {
               param1.replaceText(_loc2_,_loc2_ + 1,String.fromCharCode(8207) + ":" + String.fromCharCode(8207));
            }
            else
            {
               _loc4_ = param1.text.charCodeAt(_loc2_ + 1);
               if(_loc4_ == 32)
               {
                  _loc4_ = param1.text.charCodeAt(_loc2_ + 2);
               }
               if(_loc4_ < 32 || _loc4_ > 127)
               {
                  param1.replaceText(_loc2_,_loc2_ + 1,String.fromCharCode(8207) + ":" + String.fromCharCode(8207));
               }
            }
         }
         _loc2_ = -1;
         while(1)
         {
            _loc2_ = param1.text.indexOf(String.fromCharCode(1548),_loc2_);
            if(_loc2_ == -1)
            {
               break;
            }
            param1.replaceText(_loc2_,_loc2_ + 1,String.fromCharCode(8207) + String.fromCharCode(1548) + String.fromCharCode(8207));
            _loc2_ += 2;
         }
      }
      
      public function CheckBracketsReverse(param1:TextField) : *
      {
         var _loc3_:int = 0;
         var _loc4_:int = 0;
         var _loc5_:Number = NaN;
         var _loc2_:int = param1.text.indexOf("(");
         if(_loc2_ != -1)
         {
            _loc3_ = param1.text.indexOf(")");
            if(_loc3_ != -1)
            {
               _loc4_ = _loc2_ + 1;
               while(_loc4_ < _loc3_)
               {
                  _loc5_ = param1.text.charCodeAt(_loc4_);
                  if(_loc5_ < 32 || _loc5_ > 127)
                  {
                     break;
                  }
                  _loc4_++;
               }
               if(_loc4_ == _loc3_)
               {
                  _loc5_ = 8206;
               }
               else
               {
                  _loc5_ = 8207;
               }
               param1.replaceText(_loc3_,_loc3_ + 1,")" + String.fromCharCode(_loc5_));
               param1.replaceText(_loc2_,_loc2_ + 1,String.fromCharCode(_loc5_) + "(");
            }
         }
      }
      
      public function CreateMaskArabic(param1:MovieClip, param2:TextField, param3:Array, param4:Array, param5:Array) : *
      {
         var _loc6_:Object = null;
         var _loc14_:smb_msk = null;
         var _loc15_:int = 0;
         var _loc16_:String = null;
         var _loc17_:int = 0;
         var _loc18_:smb_msk = null;
         var _loc7_:int = -1;
         var _loc8_:int = 0;
         var _loc9_:Array = new Array();
         _loc9_.push(-1);
         _loc9_.push(-1);
         var _loc10_:int = 0;
         var _loc11_:String = "";
         var _loc12_:Rectangle = new Rectangle();
         var _loc13_:Rectangle = new Rectangle();
         if(param2.text.charAt(0) == "＠")
         {
            param2.replaceText(0,1,"");
            this.m_isEngOnly = true;
         }
         if(param2.numLines == 1)
         {
            while(1)
            {
               _loc6_ = this.GetUseKeyCodeIndex(param2.text,_loc9_,param3);
               _loc7_ = int(_loc6_[CCD_USE_INDEX]);
               if(!(_loc7_ != -1 && param4[_loc10_] != undefined))
               {
                  break;
               }
               _loc14_ = new smb_msk();
               _loc14_.blendMode = BlendMode.ERASE;
               _loc8_ = int(_loc6_[CCD_USE_KEY_CODE_TYPE]);
               _loc11_ = param3[_loc8_];
               if(this.m_isEngOnly == true)
               {
                  _loc13_ = param2.getCharBoundaries(_loc7_ + _loc11_.length - 1);
                  _loc12_ = param2.getCharBoundaries(_loc7_);
                  _loc14_.width = Math.abs(_loc12_.left - _loc13_.right);
                  _loc14_.x = _loc12_.left + _loc14_.width / 2;
               }
               else
               {
                  _loc13_ = param2.getCharBoundaries(param2.length - _loc7_ - _loc11_.length);
                  _loc12_ = param2.getCharBoundaries(param2.length - 1 - _loc7_);
                  _loc14_.width = Math.abs(_loc13_.left - _loc12_.right);
                  _loc14_.x = param2.width + param2.x - _loc12_.right + _loc14_.width / 2;
                  _loc14_.x = param2.width + param2.x - _loc14_.x;
               }
               trace("MaskX:" + _loc14_.x);
               trace("EndOnly:" + this.m_isEngOnly);
               _loc14_.height = Number(param2.defaultTextFormat.size);
               _loc14_.y = _loc12_.y + param2.y + _loc14_.height / 2 + CCD_ICON_MASK_Y_MARGIN;
               _loc14_.height += CCD_ICON_MASK_HEIGHT_MARGIN;
               param1.addChild(_loc14_);
               param5.push(_loc14_);
               _loc9_[_loc8_] = _loc7_ + param3[_loc8_].length;
               _loc10_++;
            }
         }
         else
         {
            _loc15_ = 0;
            _loc16_ = param2.getLineText(_loc15_);
            _loc17_ = _loc16_.length;
            while(1)
            {
               _loc6_ = this.GetUseKeyCodeIndex(_loc16_,_loc9_,param3);
               _loc7_ = int(_loc6_[CCD_USE_INDEX]);
               if(_loc7_ != -1 && param4[_loc10_] != undefined)
               {
                  _loc18_ = new smb_msk();
                  _loc18_.blendMode = BlendMode.ERASE;
                  _loc8_ = int(_loc6_[CCD_USE_KEY_CODE_TYPE]);
                  _loc11_ = param3[_loc8_];
                  _loc13_ = param2.getCharBoundaries(_loc17_ - _loc7_ - _loc11_.length);
                  _loc12_ = param2.getCharBoundaries(_loc17_ - 1 - _loc7_);
                  _loc18_.width = Math.abs(_loc13_.left - _loc12_.right);
                  _loc18_.x = param2.width + param2.x - _loc12_.right + _loc18_.width / 2;
                  _loc18_.x = param2.width + param2.x - _loc18_.x;
                  _loc18_.height = Number(param2.defaultTextFormat.size);
                  _loc18_.y = _loc12_.y + param2.y + _loc18_.height / 2 + CCD_ICON_MASK_Y_MARGIN;
                  param1.addChild(_loc18_);
                  param5.push(_loc18_);
                  _loc9_[_loc8_] = _loc7_ + param3[_loc8_].length;
                  _loc10_++;
               }
               else
               {
                  _loc9_[CCD_KEY_CODE] = -1;
                  _loc9_[CCD_KEY_CODE_WIDE] = -1;
                  if(++_loc15_ >= param2.numLines)
                  {
                     break;
                  }
                  _loc16_ = param2.getLineText(_loc15_);
                  _loc17_ += _loc16_.length;
               }
            }
         }
      }
      
      public function CalcMaskPosArabic(param1:TextField, param2:Array, param3:Array) : *
      {
         var _loc4_:Object = null;
         var _loc12_:int = 0;
         var _loc13_:String = null;
         var _loc14_:int = 0;
         var _loc5_:int = -1;
         var _loc6_:int = 0;
         var _loc7_:Array = new Array();
         _loc7_.push(-1);
         _loc7_.push(-1);
         var _loc8_:int = 0;
         var _loc9_:String = "";
         var _loc10_:Rectangle = new Rectangle();
         var _loc11_:Rectangle = new Rectangle();
         if(param1.numLines == 1)
         {
            while(1)
            {
               _loc4_ = this.GetUseKeyCodeIndex(param1.text,_loc7_,param2);
               _loc5_ = int(_loc4_[CCD_USE_INDEX]);
               if(!(_loc5_ != -1 && param3[_loc8_] != undefined))
               {
                  break;
               }
               _loc6_ = int(_loc4_[CCD_USE_KEY_CODE_TYPE]);
               _loc9_ = param2[_loc6_];
               if(this.m_isEngOnly == true)
               {
                  _loc11_ = param1.getCharBoundaries(_loc5_ + _loc9_.length - 1);
                  _loc10_ = param1.getCharBoundaries(_loc5_);
                  param3[_loc8_].width = Math.abs(_loc10_.left - _loc11_.right);
                  param3[_loc8_].x = _loc10_.left + param3[_loc8_].width / 2;
               }
               else
               {
                  _loc11_ = param1.getCharBoundaries(param1.length - _loc5_ - _loc9_.length);
                  _loc10_ = param1.getCharBoundaries(param1.length - 1 - _loc5_);
                  param3[_loc8_].x = param1.width + param1.x - _loc10_.right + param3[_loc8_].width / 2;
                  param3[_loc8_].x = param1.width + param1.x - param3[_loc8_].x;
               }
               param3[_loc8_].y = _loc10_.y + param1.y + param3[_loc8_].height / 2 + CCD_ICON_MASK_Y_MARGIN;
               _loc7_[_loc6_] = _loc5_ + param2[_loc6_].length;
               _loc8_++;
            }
         }
         else
         {
            _loc12_ = 0;
            _loc13_ = param1.getLineText(_loc12_);
            _loc14_ = _loc13_.length;
            while(1)
            {
               _loc4_ = this.GetUseKeyCodeIndex(_loc13_,_loc7_,param2);
               _loc5_ = int(_loc4_[CCD_USE_INDEX]);
               if(_loc5_ != -1 && param3[_loc8_] != undefined)
               {
                  _loc6_ = int(_loc4_[CCD_USE_KEY_CODE_TYPE]);
                  _loc9_ = param2[_loc6_];
                  _loc11_ = param1.getCharBoundaries(_loc14_ - _loc5_ - _loc9_.length);
                  _loc10_ = param1.getCharBoundaries(_loc14_ - 1 - _loc5_);
                  param3[_loc8_].x = param1.width + param1.x - _loc10_.right + param3[_loc8_].width / 2;
                  param3[_loc8_].x = param1.width + param1.x - param3[_loc8_].x;
                  param3[_loc8_].y = _loc10_.y + param1.y + param3[_loc8_].height / 2 + CCD_ICON_MASK_Y_MARGIN;
                  _loc7_[_loc6_] = _loc5_ + param2[_loc6_].length;
                  _loc8_++;
               }
               else
               {
                  _loc7_[CCD_KEY_CODE] = -1;
                  _loc7_[CCD_KEY_CODE_WIDE] = -1;
                  if(++_loc12_ >= param1.numLines)
                  {
                     break;
                  }
                  _loc13_ = param1.getLineText(_loc12_);
                  _loc14_ += _loc13_.length;
               }
            }
         }
      }
      
      public function CalcArabicTag(param1:TextField) : *
      {
         var _loc2_:int = -1;
         while(1)
         {
            _loc2_ = param1.text.indexOf(CCD_TAG_LTR_MARK,_loc2_);
            if(_loc2_ == -1)
            {
               break;
            }
            param1.replaceText(_loc2_,_loc2_ + CCD_TAG_LTR_MARK.length,String.fromCharCode(8206));
         }
         while(1)
         {
            _loc2_ = param1.text.indexOf(CCD_TAG_RTL_MARK,_loc2_);
            if(_loc2_ == -1)
            {
               break;
            }
            param1.replaceText(_loc2_,_loc2_ + CCD_TAG_LTR_MARK.length,String.fromCharCode(8207));
         }
      }
   }
}

