package script.hist_mov
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public class smb_tlp extends MovieClip
   {
      
      public var txt_tlp:smb_font;
      
      private var m_txt:smb_font = null;
      
      public function smb_tlp()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_txt = this["txt_tlp"];
      }
      
      public function SetText(param1:String) : *
      {
         this.m_txt.SetText(param1);
      }
      
      internal function frame1() : *
      {
         this.txt_tlp.SetTextSize(50);
         this.txt_tlp.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_tlp.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_tlp.SetTextFieldWidth(1640);
         this.txt_tlp.SetTextFit(true);
      }
   }
}

