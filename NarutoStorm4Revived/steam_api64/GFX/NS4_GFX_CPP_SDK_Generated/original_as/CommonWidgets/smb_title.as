package script.start_item
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public class smb_title extends MovieClip
   {
      
      public var mc_txt_item:MovieClip;
      
      public var mc_txt_own:MovieClip;
      
      public function smb_title()
      {
         super();
         if(this.mc_txt_item.txt_item.IsArabic() == true)
         {
            this.mc_txt_item.x = -this.mc_txt_item.x;
            this.mc_txt_own.x = -this.mc_txt_own.x;
         }
      }
   }
}

