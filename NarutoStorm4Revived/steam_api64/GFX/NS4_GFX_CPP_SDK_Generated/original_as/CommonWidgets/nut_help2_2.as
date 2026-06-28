package script.net_bingo
{
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import script.net_cmn.smb_win;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol14")]
   public class nut_help2 extends MovieClip
   {
      
      public var smb_win:script.net_cmn.smb_win;
      
      public var txt_get:smb_font;
      
      private var m_getTxt:smb_font = null;
      
      private var m_getTxtNum:smb_font = null;
      
      public function nut_help2()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_getTxt = this["txt_get"];
         this.m_getTxt.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.m_getTxt.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         this.m_getTxt.SetText(String(ExternalInterface.call("MessageConvert","network_sys_201")));
         this.m_getTxt.visible = false;
      }
      
      public function SetNextRewardInfo(param1:uint, param2:uint, param3:String) : *
      {
         var _loc4_:uint = param2 - param1;
         var _loc5_:Array = new Array();
         _loc5_.push(param3);
         _loc5_.push(_loc4_.toString());
         this.m_getTxt.visible = true;
         this.m_getTxt.ReplaceTextList(_loc5_);
      }
      
      internal function frame1() : *
      {
         this.txt_get.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_get.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_get.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_get.SetTextFieldWidth(1454);
         this.txt_get.SetTextFit(true);
      }
   }
}

