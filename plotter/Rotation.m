classdef Rotation
   properties
       R;
   end
   methods
       function obj = Rotation(varargin)
           if nargin<2
                obj.R = varargin{1};
           else
              angle = varargin{1};
              axis =  varargin{2};
              if (axis == 'z')
                  obj.R = [cos(angle) sin(angle) 0;-sin(angle) cos(angle) 0; 0 0 1];
              elseif (axis == 'y')
                  obj.R = [cos(angle) 0 -sin(angle) ; 0 1 0; sin(angle) 0 cos(angle)];
              elseif (axis == 'x')
                  obj.R = [1 0 0 ; 0 cos(angle) sin(angle); 0 -sin(angle) cos(angle)];
              end 
           end
       end
      function a = Rotate(obj,v3D)
          a = vector3D(obj.R*v3D.v);
      end 
      function result = mtimes(obj,B)
          if class(B) == "Rotation"
            result = Rotation(obj.R*B.R);
          elseif class(B) == "vector3D"
            result = vector3D(obj.R*B.v);
          end
      end
   end
end
