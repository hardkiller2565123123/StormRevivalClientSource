package script.shop_cmn
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base4;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public class nut_tab extends MovieClip
   {
      
      public var all_base4:nut_base4;
      
      public var txt_tab:smb_font;
      
      public function nut_tab()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_tab.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_tab.SetTextColor(14013909);
         this.txt_tab.SetTextSize(30);
      }
   }
}

