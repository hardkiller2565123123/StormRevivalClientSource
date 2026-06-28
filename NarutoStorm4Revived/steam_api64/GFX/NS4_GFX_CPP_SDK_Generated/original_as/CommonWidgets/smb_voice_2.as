package script.gametitle
{
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import script.xcmn_font.smb_font;
   import script.xcmn_set.smb_txtbar_base;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol16")]
   public class smb_voice extends MovieClip
   {
      
      private static const CCD_BAR_MARGIN:Number = 200;
      
      public var mc_bar:smb_txtbar_base;
      
      public var mc_font:smb_font;
      
      private var m_txt:smb_font = null;
      
      private var m_bar:MovieClip = null;
      
      public function smb_voice()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_txt = this["mc_font"];
         this.m_bar = this["mc_bar"];
      }
      
      public function SetText(param1:String) : *
      {
         var _loc2_:Array = new Array();
         _loc2_.push(param1);
         this.m_txt.SetText(String(ExternalInterface.call("MessageConvert","MSG_demo_006")));
         this.m_txt.ReplaceTextList(_loc2_);
         this.m_bar.width = this.m_txt.GetTextFieldWidth() + CCD_BAR_MARGIN;
      }
      
      internal function frame1() : *
      {
         this.mc_font.SetTextPivot(smb_font.CCD_PIVOT_RC);
      }
   }
}

