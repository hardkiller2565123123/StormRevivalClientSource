package script.net_cmn
{
   import Enum.Enum;
   import InputPad.InputPadKeyCode;
   import KeyHelp.KeyHelpCode;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.ExternalInterface;
   import script.xcmn_menu.nut_cursor_m;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol25")]
   public class nut_net_result extends MovieClip
   {
      
      internal static var UI_TEXT_USER_ID:Number = Enum.Next(0);
      
      internal static var UI_TEXT_ITEM_TITLE:Number = Enum.Next();
      
      internal static var UI_TEXT_TITLE_00:Number = Enum.Next();
      
      internal static var UI_TEXT_TITLE_01:Number = Enum.Next();
      
      internal static var UI_TEXT_ITEM_RANK:Number = Enum.Next();
      
      internal static var UI_TEXT_RANK_NAME:Number = Enum.Next();
      
      internal static var UI_TEXT_RANK_NAME01:Number = Enum.Next();
      
      internal static var UI_TEXT_ITEM_BP:Number = Enum.Next();
      
      internal static var UI_TEXT_BP:Number = Enum.Next();
      
      internal static var UI_TEXT_ITEM_BTL_TYPE:Number = Enum.Next();
      
      internal static var UI_TEXT_ITEM_PLAYER_BATTLE:Number = Enum.Next();
      
      internal static var UI_TEXT_WIN_PLAY_TITLE:Number = Enum.Next();
      
      internal static var UI_TEXT_WIN_PLAY:Number = Enum.Next();
      
      internal static var UI_TEXT_ITEM_LEAGUE:Number = Enum.Next();
      
      internal static var UI_TEXT_ITEM_LEG_CHAMPION:Number = Enum.Next();
      
      internal static var UI_TEXT_LEG_CHAMPION:Number = Enum.Next();
      
      internal static var UI_TEXT_ITEM_TOURNAMENT:Number = Enum.Next();
      
      internal static var UI_TEXT_ITEM_TMT_CHAMPION:Number = Enum.Next();
      
      internal static var UI_TEXT_TMT_CHAMPION:Number = Enum.Next();
      
      internal static var UI_TEXT_ITEM_ENDLESS:Number = Enum.Next();
      
      internal static var UI_TEXT_ENDLESS_TITLE:Number = Enum.Next();
      
      internal static var UI_TEXT_ENDLESS:Number = Enum.Next();
      
      internal static var UI_TEXT_CHAR_FREQUENCY:Number = Enum.Next();
      
      internal static var UI_TEXT_CHAR_00:Number = Enum.Next();
      
      internal static var UI_TEXT_CHAR_01:Number = Enum.Next();
      
      internal static var UI_TEXT_CHAR_02:Number = Enum.Next();
      
      internal static var UI_TEXT_RANK_MATCH:Number = Enum.Next();
      
      internal static var UI_TEXT_BATTLE_RANK:Number = Enum.Next();
      
      internal static var UI_TEXT_WIN_RANK:Number = Enum.Next();
      
      internal static var UI_TEXT_WIN_PERCENT_TITLE:Number = Enum.Next();
      
      internal static var UI_TEXT_WIN_PERCENT:Number = Enum.Next();
      
      internal static var UI_TEXT_ITEM_DISCONNECTION:Number = Enum.Next();
      
      internal static var UI_TEXT_DISCONNECTION:Number = Enum.Next();
      
      internal static var UI_TEXT_NUM:* = Enum.Next();
      
      public var all_cursor_b:nut_cursor_m;
      
      public var all_cursor_t:nut_cursor_m;
      
      public var mc_result_win:anm_result_win;
      
      public var mc_txt:smb_txt;
      
      internal var m_input:InputPadKeyCode;
      
      internal var m_keyHelp:KeyHelpCode;
      
      internal var m_end:Boolean = false;
      
      internal var m_start:Boolean = false;
      
      public function nut_net_result()
      {
         super();
         addFrameScript(4,this.frame5,8,this.frame9);
         this.m_end = false;
         if(this.mc_txt.IsArabicLayout() == true)
         {
            this.mc_result_win.ChangeArabicLayout();
         }
      }
      
      public function IsEnd() : Boolean
      {
         if(this.currentLabel == "end")
         {
            return true;
         }
         return false;
      }
      
      public function SetParam(param1:int, param2:String) : *
      {
         var _loc3_:MovieClip = this.mc_txt;
         if(_loc3_ == null)
         {
            trace("#net_cmn result error SetParam ");
         }
         var _loc4_:MovieClip = this.GetMc(param1);
         if(_loc4_)
         {
            if(UI_TEXT_TITLE_00 == param1)
            {
               _loc4_.SetTextFieldWidth(550);
               _loc4_.SetTextFit(true);
            }
            if(UI_TEXT_TITLE_01 == param1)
            {
               _loc4_.SetTextFieldWidth(550);
               _loc4_.SetTextFit(true);
            }
            _loc4_.SetText(param2);
         }
         else
         {
            trace("#net_cmn result error id " + param1);
         }
      }
      
      public function GetMc(param1:int) : MovieClip
      {
         var _loc2_:MovieClip = this.mc_txt;
         switch(param1)
         {
            case UI_TEXT_USER_ID:
               return _loc2_.txt_userid;
            case UI_TEXT_ITEM_TITLE:
               return _loc2_.txt_name_h;
            case UI_TEXT_TITLE_00:
               return _loc2_.txt_name1;
            case UI_TEXT_TITLE_01:
               return _loc2_.txt_name2;
            case UI_TEXT_ITEM_RANK:
               return _loc2_.txt_rank_h;
            case UI_TEXT_RANK_NAME:
               return _loc2_.txt_rank;
            case UI_TEXT_RANK_NAME01:
               return _loc2_.txt_rank_num;
            case UI_TEXT_ITEM_BP:
               return _loc2_.txt_bp_h;
            case UI_TEXT_BP:
               return _loc2_.txt_bp_num;
            case UI_TEXT_ITEM_BTL_TYPE:
               return _loc2_.txt_btl_h;
            case UI_TEXT_ITEM_PLAYER_BATTLE:
               return _loc2_.txt_play_h;
            case UI_TEXT_WIN_PLAY_TITLE:
               return _loc2_.txt_play_wins;
            case UI_TEXT_WIN_PLAY:
               return _loc2_.txt_play_wins_num;
            case UI_TEXT_ITEM_LEAGUE:
               return _loc2_.txt_leag_h;
            case UI_TEXT_ITEM_LEG_CHAMPION:
               return _loc2_.txt_leag_wins;
            case UI_TEXT_LEG_CHAMPION:
               return _loc2_.txt_leag_wins_num;
            case UI_TEXT_ITEM_TOURNAMENT:
               return _loc2_.txt_tonmt_h;
            case UI_TEXT_ITEM_TMT_CHAMPION:
               return _loc2_.txt_tonmt_wins;
            case UI_TEXT_TMT_CHAMPION:
               return _loc2_.txt_tonmt_num;
            case UI_TEXT_ITEM_ENDLESS:
               return _loc2_.txt_endls_h;
            case UI_TEXT_ENDLESS_TITLE:
               return _loc2_.txt_endls_wins;
            case UI_TEXT_ENDLESS:
               return _loc2_.txt_endls_num;
            case UI_TEXT_CHAR_FREQUENCY:
               return _loc2_.txt_usechara_h;
            case UI_TEXT_CHAR_00:
               return _loc2_.txt_chara_name1;
            case UI_TEXT_CHAR_01:
               return _loc2_.txt_chara_name2;
            case UI_TEXT_CHAR_02:
               return _loc2_.txt_chara_name3;
            case UI_TEXT_RANK_MATCH:
               return _loc2_.txt_rmach_h;
            case UI_TEXT_BATTLE_RANK:
               return _loc2_.txt_rmach_btl;
            case UI_TEXT_WIN_RANK:
               return _loc2_.txt_rmach_wins;
            case UI_TEXT_WIN_PERCENT_TITLE:
               return _loc2_.txt_wins_per;
            case UI_TEXT_WIN_PERCENT:
               return _loc2_.txt_per_num;
            case UI_TEXT_ITEM_DISCONNECTION:
               return _loc2_.txt_discon;
            case UI_TEXT_DISCONNECTION:
               return _loc2_.txt_discon_num;
            default:
               return null;
         }
      }
      
      public function AllClearParam() : *
      {
         var _loc1_:int = 0;
         while(_loc1_ < UI_TEXT_NUM)
         {
            this.SetParam(_loc1_,"");
            _loc1_++;
         }
      }
      
      public function CallInit() : *
      {
         this.m_end = false;
         this.visible = false;
         stop();
      }
      
      public function CallStart() : *
      {
         if(this.m_start == false)
         {
            this.m_input = new InputPadKeyCode();
            this.m_keyHelp = new KeyHelpCode();
            this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_CANCEL,"MSG_Close");
            this.m_keyHelp.PushKeyHelp();
            addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
            this.visible = true;
            this.m_start = true;
            gotoAndPlay("in");
         }
      }
      
      public function CallClose() : *
      {
         this.m_end = true;
         this.m_keyHelp.PopKeyHelp();
         gotoAndPlay("out");
      }
      
      public function onEnterFrameCtrl(param1:Event) : *
      {
         if(this.m_end == false)
         {
            if(this.m_input)
            {
               if(this.m_input.GetPadPress() & this.m_input.GetKeyInputBtn_Cancel())
               {
                  ExternalInterface.call("RequestPlaySE_Cancel");
                  if(this.currentLabel != "out")
                  {
                     this.m_end = true;
                     this.m_keyHelp.PopKeyHelp();
                     gotoAndPlay("out");
                  }
               }
            }
         }
      }
      
      internal function frame5() : *
      {
         stop();
      }
      
      internal function frame9() : *
      {
         stop();
      }
   }
}

