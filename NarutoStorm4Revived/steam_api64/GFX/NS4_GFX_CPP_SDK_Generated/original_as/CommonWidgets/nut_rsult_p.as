package script.net_result
{
   import Enum.Enum_NetLabel;
   import flash.display.MovieClip;
   import flash.external.*;
   import script.icon_result.smb_btl;
   import script.icon_result.smb_win;
   import script.net_icon.nut_type;
   import script.xcmn_font.smb_font;
   import script.xcmn_net.nut_icon_wave;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol9")]
   public class nut_rsult_p extends MovieClip
   {
      
      internal static var UI_TEXT_MATCH:Number = 0;
      
      internal static var UI_TEXT_BTL_NUM:Number = 1;
      
      internal static var UI_TEXT_WIN_NUM:Number = 2;
      
      internal static var UI_TEXT_WIN_PARCENT:Number = 3;
      
      internal static var UI_TEXT_DISCONEECT_NUM:Number = 4;
      
      internal static var UI_TEXT_WIN_TOP:Number = 5;
      
      public var txt_wins_per:smb_font;
      
      public var txt_match_h:smb_font;
      
      public var mc_btl:smb_btl;
      
      public var mc_win:smb_win;
      
      public var all_icon_status:nut_type;
      
      public var all_icon_info:nut_type;
      
      public var txt_discon:smb_font;
      
      public var txt_discon_num:smb_font;
      
      public var txt_win_top:smb_font;
      
      public var txt_wins_num:smb_font;
      
      public var all_icon_wave:nut_icon_wave;
      
      public var txt_btl_num:smb_font;
      
      public var txt_per_num:smb_font;
      
      private var m_type:int = 0;
      
      public function nut_rsult_p()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
         gotoAndStop(2);
      }
      
      public function Initialize() : *
      {
      }
      
      public function SetResultPlate_Friend(param1:Boolean, param2:int) : *
      {
         var _loc3_:MovieClip = getChildByName("all_icon_status") as MovieClip;
         if(_loc3_)
         {
            switch(param2)
            {
               case Enum_NetLabel.CCD_UI_NET_RESULT_PLATE_FRIEND_INVISIBLE:
                  _loc3_.visible = false;
                  break;
               case Enum_NetLabel.CCD_UI_NET_RESULT_PLATE_FRIEND_ON:
                  _loc3_.gotoAndStop("friend_on");
                  _loc3_.visible = true;
                  break;
               case Enum_NetLabel.CCD_UI_NET_RESULT_PLATE_FRIEND_OFF:
                  _loc3_.gotoAndStop("friend_off");
                  _loc3_.visible = true;
            }
         }
      }
      
      public function SetResultPlate_Wave(param1:Boolean, param2:int, param3:Boolean) : *
      {
         var _loc4_:MovieClip = getChildByName("all_icon_wave") as MovieClip;
         if(_loc4_)
         {
            if(param3 == false)
            {
               _loc4_.visible = false;
               return;
            }
            if(param1)
            {
               _loc4_.visible = false;
               return;
            }
            if(param2 == 0)
            {
               _loc4_.visible = false;
            }
            else if(param2 > 1)
            {
               _loc4_.visible = true;
               if(param2 < 25)
               {
                  _loc4_.gotoAndStop(6);
               }
               else if(param2 < 57)
               {
                  _loc4_.gotoAndStop(7);
               }
               else if(param2 < 90)
               {
                  _loc4_.gotoAndStop(8);
               }
               else if(param2 < 123)
               {
                  _loc4_.gotoAndStop(9);
               }
               else if(param2 < 155)
               {
                  _loc4_.gotoAndStop(10);
               }
               else if(param2 < 188)
               {
                  _loc4_.gotoAndStop(11);
               }
               else if(param2 < 221)
               {
                  _loc4_.gotoAndStop(12);
               }
               else if(param2 < 253)
               {
                  _loc4_.gotoAndStop(13);
               }
               else if(param2 < 286)
               {
                  _loc4_.gotoAndStop(14);
               }
               else
               {
                  _loc4_.gotoAndStop(15);
               }
            }
            else
            {
               _loc4_.visible = true;
               if(param2 > -9)
               {
                  _loc4_.gotoAndStop(16);
               }
               else if(param2 > -25)
               {
                  _loc4_.gotoAndStop(17);
               }
               else if(param2 > -41)
               {
                  _loc4_.gotoAndStop(18);
               }
               else if(param2 > -57)
               {
                  _loc4_.gotoAndStop(19);
               }
               else if(param2 > -74)
               {
                  _loc4_.gotoAndStop(20);
               }
               else if(param2 > -90)
               {
                  _loc4_.gotoAndStop(21);
               }
               else if(param2 > -106)
               {
                  _loc4_.gotoAndStop(22);
               }
               else if(param2 > -123)
               {
                  _loc4_.gotoAndStop(23);
               }
               else if(param2 > -139)
               {
                  _loc4_.gotoAndStop(24);
               }
               else if(param2 > -155)
               {
                  _loc4_.gotoAndStop(25);
               }
               else if(param2 > -172)
               {
                  _loc4_.gotoAndStop(26);
               }
               else if(param2 > -188)
               {
                  _loc4_.gotoAndStop(27);
               }
               else if(param2 > -204)
               {
                  _loc4_.gotoAndStop(28);
               }
               else if(param2 > -221)
               {
                  _loc4_.gotoAndStop(29);
               }
               else if(param2 > -237)
               {
                  _loc4_.gotoAndStop(30);
               }
               else if(param2 > -253)
               {
                  _loc4_.gotoAndStop(31);
               }
               else if(param2 > -270)
               {
                  _loc4_.gotoAndStop(32);
               }
               else if(param2 > -286)
               {
                  _loc4_.gotoAndStop(33);
               }
               else
               {
                  _loc4_.gotoAndStop(34);
               }
            }
         }
      }
      
      public function SetResultPlate_Info(param1:Boolean, param2:int, param3:Boolean) : *
      {
         var _loc4_:MovieClip = getChildByName("all_icon_info") as MovieClip;
         if(_loc4_)
         {
            if(param3 == false)
            {
               _loc4_.visible = false;
               return;
            }
            switch(param2)
            {
               case Enum_NetLabel.CCD_UI_NET_RESULT_PLATE_VOICE_NO:
                  _loc4_.gotoAndStop("voice_off");
                  _loc4_.visible = true;
                  break;
               case Enum_NetLabel.CCD_UI_NET_RESULT_PLATE_VOICE_HEAD:
                  _loc4_.gotoAndStop("voice_on");
                  _loc4_.visible = true;
                  break;
               case Enum_NetLabel.CCD_UI_NET_RESULT_PLATE_VOICE_CHAT_ON:
                  _loc4_.gotoAndStop("hedset_on");
                  _loc4_.visible = true;
                  break;
               case Enum_NetLabel.CCD_UI_NET_RESULT_PLATE_VOICE_CHAT_OFF:
                  _loc4_.gotoAndStop("hedset_off");
                  _loc4_.visible = true;
                  break;
               default:
                  _loc4_.visible = false;
            }
         }
      }
      
      public function SetType(param1:int) : *
      {
         var _loc2_:MovieClip = null;
         this.m_type = param1;
         switch(this.m_type)
         {
            case 0:
               gotoAndStop("lay_1");
               break;
            case 1:
               gotoAndStop("lay_2");
               break;
            case 2:
               gotoAndStop("lay_3");
               break;
            case 3:
               gotoAndStop("lay_3");
               break;
            case 4:
               gotoAndStop("lay_3");
         }
      }
      
      public function SetBaseText() : *
      {
         var _loc1_:MovieClip = null;
         switch(this.m_type)
         {
            case 0:
               _loc1_ = this.getChildByName("txt_per_num") as MovieClip;
               if(_loc1_ != null)
               {
                  _loc1_.visible = true;
                  _loc1_ = null;
               }
               _loc1_ = this.getChildByName("txt_match_h") as MovieClip;
               if(_loc1_ != null)
               {
                  _loc1_.SetText(String(ExternalInterface.call("MessageConvert","network_sys_064")));
                  _loc1_ = null;
               }
               _loc1_ = this.getChildByName("txt_wins_per") as MovieClip;
               if(_loc1_ != null)
               {
                  _loc1_.SetText(String(ExternalInterface.call("MessageConvert","network_ranking_012")));
                  _loc1_ = null;
               }
               _loc1_ = this.getChildByName("txt_discon") as MovieClip;
               if(_loc1_ != null)
               {
                  _loc1_.SetText(String(ExternalInterface.call("MessageConvert","networkmode_133")));
                  _loc1_ = null;
               }
               break;
            case 1:
               _loc1_ = this.getChildByName("txt_match_h") as MovieClip;
               if(_loc1_ != null)
               {
                  _loc1_.SetText(String(ExternalInterface.call("MessageConvert","network_sys_061")));
                  _loc1_ = null;
               }
               _loc1_ = this.getChildByName("txt_discon") as MovieClip;
               if(_loc1_ != null)
               {
                  _loc1_.SetText(String(ExternalInterface.call("MessageConvert","networkmode_133")));
                  _loc1_ = null;
               }
               break;
            case 2:
               _loc1_ = this.getChildByName("txt_match_h") as MovieClip;
               if(_loc1_ != null)
               {
                  _loc1_.SetText(String(ExternalInterface.call("MessageConvert","network_sys_168")));
                  _loc1_ = null;
               }
               _loc1_ = this.getChildByName("txt_win_top") as MovieClip;
               if(_loc1_ != null)
               {
                  _loc1_.SetText(String(ExternalInterface.call("MessageConvert","networkmode_180")));
                  _loc1_ = null;
               }
               _loc1_ = this.getChildByName("txt_discon") as MovieClip;
               if(_loc1_ != null)
               {
                  _loc1_.SetText(String(ExternalInterface.call("MessageConvert","networkmode_133")));
                  _loc1_ = null;
               }
               break;
            case 3:
               _loc1_ = this.getChildByName("txt_match_h") as MovieClip;
               if(_loc1_ != null)
               {
                  _loc1_.SetText(String(ExternalInterface.call("MessageConvert","network_sys_167")));
                  _loc1_ = null;
               }
               _loc1_ = this.getChildByName("txt_win_top") as MovieClip;
               if(_loc1_ != null)
               {
                  _loc1_.SetText(String(ExternalInterface.call("MessageConvert","networkmode_180")));
                  _loc1_ = null;
               }
               _loc1_ = this.getChildByName("txt_discon") as MovieClip;
               if(_loc1_ != null)
               {
                  _loc1_.SetText(String(ExternalInterface.call("MessageConvert","networkmode_133")));
                  _loc1_ = null;
               }
               break;
            case 4:
               _loc1_ = this.getChildByName("txt_match_h") as MovieClip;
               if(_loc1_ != null)
               {
                  _loc1_.SetText(String(ExternalInterface.call("MessageConvert","network_sys_166")));
                  _loc1_ = null;
               }
               _loc1_ = this.getChildByName("txt_win_top") as MovieClip;
               if(_loc1_ != null)
               {
                  _loc1_.SetText(String(ExternalInterface.call("MessageConvert","network_sys_035")));
                  _loc1_ = null;
               }
               _loc1_ = this.getChildByName("txt_discon") as MovieClip;
               if(_loc1_ != null)
               {
                  _loc1_.SetText(String(ExternalInterface.call("MessageConvert","networkmode_133")));
                  _loc1_ = null;
               }
         }
      }
      
      public function SetParam(param1:int, param2:String) : *
      {
         var _loc3_:MovieClip = this;
         switch(param1)
         {
            case UI_TEXT_MATCH:
               _loc3_.txt_match_h.SetText(param2);
               break;
            case UI_TEXT_BTL_NUM:
               _loc3_.txt_btl_num.SetText(param2);
               break;
            case UI_TEXT_WIN_NUM:
               _loc3_.txt_wins_num.SetText(param2);
               break;
            case UI_TEXT_WIN_PARCENT:
               _loc3_.txt_per_num.SetText(param2);
               break;
            case UI_TEXT_DISCONEECT_NUM:
               _loc3_.txt_discon_num.SetText(param2);
               break;
            case UI_TEXT_WIN_TOP:
               _loc3_.txt_win_top.SetText(param2);
         }
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_match_h.SetTextSize(28);
         this.txt_match_h.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_match_h.SetTextColor(15721077);
         this.txt_match_h.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_match_h.SetTextFieldWidth(400);
         this.txt_match_h.SetTextFit(true);
         this.txt_btl_num.SetTextSize(28);
         this.txt_btl_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_btl_num.SetTextColor(2169344);
         this.txt_wins_num.SetTextSize(28);
         this.txt_wins_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_wins_num.SetTextColor(2169344);
         this.txt_wins_per.SetTextSize(28);
         this.txt_wins_per.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_per_num.SetTextSize(28);
         this.txt_per_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_discon.SetTextSize(28);
         this.txt_discon.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_discon.SetTextFieldWidth(300);
         this.txt_discon.SetTextFit(true);
         this.txt_discon_num.SetTextSize(28);
         this.txt_discon_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_match_h.SetTextSize(28);
         this.txt_match_h.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_match_h.SetTextColor(15721077);
         this.txt_match_h.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_match_h.SetTextFieldWidth(400);
         this.txt_match_h.SetTextFit(true);
         this.txt_wins_num.SetTextSize(28);
         this.txt_wins_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_wins_num.SetTextColor(2169344);
         this.txt_discon.SetTextSize(28);
         this.txt_discon.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_discon.SetTextFieldWidth(300);
         this.txt_discon.SetTextFit(true);
         this.txt_discon_num.SetTextSize(28);
         this.txt_discon_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
      }
      
      internal function frame3() : *
      {
         stop();
         this.txt_match_h.SetTextSize(28);
         this.txt_match_h.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_match_h.SetTextColor(15721077);
         this.txt_match_h.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_match_h.SetTextFieldWidth(400);
         this.txt_match_h.SetTextFit(true);
         this.txt_btl_num.SetTextSize(28);
         this.txt_btl_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_btl_num.SetTextColor(2169344);
         this.txt_wins_num.SetTextSize(28);
         this.txt_wins_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_wins_num.SetTextColor(2169344);
         this.txt_win_top.SetTextSize(28);
         this.txt_win_top.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_win_top.SetTextColor(2169344);
         this.txt_discon.SetTextSize(28);
         this.txt_discon.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_discon.SetTextFieldWidth(300);
         this.txt_discon.SetTextFit(true);
         this.txt_discon_num.SetTextSize(28);
         this.txt_discon_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
      }
   }
}

