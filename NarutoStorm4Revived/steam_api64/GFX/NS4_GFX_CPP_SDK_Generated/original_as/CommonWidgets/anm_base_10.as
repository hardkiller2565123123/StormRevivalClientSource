package map_sm_brt_fla
{
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol54")]
   public dynamic class anm_base_10 extends MovieClip
   {
      
      public var txt_point:smb_font;
      
      public function anm_base_10()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_point.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_point.SetTextSize(28);
         this.txt_point.SetTextColor(16771175);
         this.txt_point.SetTextFieldWidth(600);
         this.txt_point.SetTextScroll(true);
         this.txt_point.SetText(String(ExternalInterface.call("MessageConvert","advMainMenu_034")));
      }
   }
}

