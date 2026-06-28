package script.hist_mov
{
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol6")]
   public class nut_tlp extends MovieClip
   {
      
      public var mc_tlp:smb_tlp;
      
      public var mc_plt:MovieClip;
      
      private const CCD_DEFAULT_WIDTH:Number = 440;
      
      private var m_tlpTxt:smb_tlp;
      
      private var m_plate:MovieClip;
      
      public function nut_tlp()
      {
         super();
         addFrameScript(24,this.frame25,49,this.frame50);
         this.m_tlpTxt = this["mc_tlp"];
         this.m_plate = this["mc_plt"];
      }
      
      public function SetTextNextChapter() : *
      {
         this.m_tlpTxt.SetText(String(ExternalInterface.call("MessageConvert","texture_UI_203")));
         this.SetPlateWidth();
      }
      
      public function SetTextSummary() : *
      {
         this.m_tlpTxt.SetText(String(ExternalInterface.call("MessageConvert","advMainMenu_016")));
         this.SetPlateWidth();
      }
      
      private function SetPlateWidth() : *
      {
         if(this.m_tlpTxt.width > this.CCD_DEFAULT_WIDTH)
         {
            this.m_plate.width += this.m_tlpTxt.width - this.CCD_DEFAULT_WIDTH;
         }
      }
      
      internal function frame25() : *
      {
         this.stop();
      }
      
      internal function frame50() : *
      {
         this.stop();
      }
   }
}

