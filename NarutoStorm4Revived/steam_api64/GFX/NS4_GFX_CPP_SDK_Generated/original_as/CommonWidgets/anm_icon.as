package script.xcmn_font
{
   import flash.display.Bitmap;
   import flash.display.BitmapData;
   import flash.display.MovieClip;
   import flash.geom.ColorTransform;
   import flash.utils.getDefinitionByName;
   
   public class anm_icon extends MovieClip
   {
      
      private const CCD_ICON_X:Number = -43;
      
      private const CCD_ICON_Y:Number = -35;
      
      private const CCD_SHADOW_DISTANCE_X:Number = 6;
      
      private const CCD_SHADOW_DISTANCE_Y:Number = 6;
      
      private var m_icon:Bitmap = null;
      
      private var m_bmpData:BitmapData = null;
      
      public function anm_icon()
      {
         super();
      }
      
      public function CreateIcon(param1:uint) : *
      {
         var _loc3_:ColorTransform = null;
         var _loc2_:Class = getDefinitionByName(currentFrameLabel) as Class;
         this.m_bmpData = new _loc2_(0,0);
         this.m_icon = new Bitmap(this.m_bmpData);
         this.m_icon.smoothing = true;
         this.m_icon.x = this.CCD_ICON_X;
         this.m_icon.y = this.CCD_ICON_Y;
         if(currentFrameLabel.indexOf("icon") == -1)
         {
            _loc3_ = new ColorTransform();
            _loc3_.color = param1;
            this.m_icon.transform.colorTransform = _loc3_;
         }
         this.addChildAt(this.m_icon,0);
      }
   }
}

